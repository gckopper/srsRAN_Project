/*
 *
 * Copyright 2013-2022 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "gnb_console_helper.h"
#include "string_helpers.h"
#include "srsgnb/ran/band_helper.h"
#include "srsgnb/support/build_info/build_info.h"
#include <list>
#include <signal.h>
#include <unistd.h>

using namespace srsgnb;

gnb_console_helper::gnb_console_helper(io_broker& io_broker_) :
  logger(srslog::fetch_basic_logger("GNB")), io_broker_handle(io_broker_)
{
  // set STDIN file descripter into non-blocking mode
  int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
  if (fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK) == -1) {
    logger.error("Couldn't configure fd to non-blocking.");
  }

  if (io_broker_handle.register_fd(STDIN_FILENO, [this](int fd) { stdin_handler(fd); }) == false) {
    logger.error("Couldn't register stdin hanlder.");
  }
}

gnb_console_helper::~gnb_console_helper()
{
  io_broker_handle.unregister_fd(STDIN_FILENO);
}

void gnb_console_helper::stdin_handler(int fd)
{
  static const unsigned               read_chunk = 256;
  std::array<uint8_t, 4 * read_chunk> buffer;
  int                                 bytes_read       = 0;
  int                                 total_bytes_read = 0;

  logger.debug("Stdin has data to read");

  do {
    // read from stdin until EWOULDBLOCK is set
    bytes_read = read(fd, &buffer[total_bytes_read], read_chunk);
    if (bytes_read < 0) {
      if (errno == EWOULDBLOCK || errno == EAGAIN || errno == EINTR) {
        break;
      }
    } else if (bytes_read == 0) {
      logger.debug("Connection closed\n");
      return;
    } else {
      total_bytes_read += bytes_read;
      if (total_bytes_read + read_chunk > buffer.size()) {
        logger.error("Can't read more than {} B from stdin.\n", buffer.size());
        return;
      }
    }
  } while (true);

  logger.debug("read {} B from stdin\n", total_bytes_read);

  // convert buffer to string
  std::string input_line(buffer.begin(), buffer.begin() + total_bytes_read);

  std::list<std::string> cmd_list;
  srsgnb::string_parse_list(input_line, ';', cmd_list);
  for (auto& cmd : cmd_list) {
    cmd.erase(std::remove(cmd.begin(), cmd.end(), '\n'), cmd.cend());
    handle_command(cmd);
  }
}

void gnb_console_helper::handle_command(const std::string& command)
{
  if (command == "q") {
    raise(SIGTERM);
  } else if (command == "t") {
    metrics_plotter.toggle_print();
  } else {
    print_help();
  }
}

void gnb_console_helper::print_help()
{
  fmt::print("Available commands:\n");
  fmt::print("\tt: starts console trace\n");
  fmt::print("\tq: quit application\n");
  fmt::print("\n");
}

void gnb_console_helper::set_cells(const std::vector<du_cell_config>& cells_)
{
  cells = cells_;
}

void gnb_console_helper::on_start_begin()
{
  fmt::print("\n--== srsRAN gNB (build={}, {}) ==--\n\n", get_build_mode(), get_build_info());
}

void gnb_console_helper::on_start_complete()
{
  for (const auto& cell : cells) {
    fmt::print("Cell pci={}, bw={} MHz, dl_arfcn={} (n{}), dl_freq={} MHz, dl_ssb_arfcn={}, ul_freq={} MHz\n",
               cell.pci,
               cell.dl_carrier.carrier_bw_mhz,
               cell.dl_carrier.arfcn,
               srsgnb::nr_band_to_uint(cell.dl_carrier.band),
               srsgnb::band_helper::nr_arfcn_to_freq(cell.dl_carrier.arfcn) / 1e6,
               0 /* FIXME: SSB-ARFCN field/derivation missing */,
               srsgnb::band_helper::nr_arfcn_to_freq(cell.ul_carrier.arfcn) / 1e6);
  }
  fmt::print("\n");

  fmt::print("==== gNodeB started ===\n");
  fmt::print("Type <t> to view trace\n");
}

void gnb_console_helper::on_stop_begin()
{
  fmt::print("Stopping ..\n");
}