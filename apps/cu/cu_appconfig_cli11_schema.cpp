/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * This file is part of srsRAN.
 *
 * srsRAN is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsRAN is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * A copy of the GNU Affero General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */

#include "cu_appconfig_cli11_schema.h"
#include "cu_appconfig.h"
#include "srsran/support/cli11_utils.h"
#include "CLI/CLI11.hpp"

using namespace srsran;

// TODO this is common between DU and CU.
static void configure_cli11_log_args(CLI::App& app, log_appconfig& log_params)
{
  auto level_check = [](const std::string& value) -> std::string {
    if (value == "info" || value == "debug" || value == "warning" || value == "error") {
      return {};
    }
    return "Log level value not supported. Accepted values [info,debug,warning,error]";
  };

  auto metric_level_check = [](const std::string& value) -> std::string {
    if (value == "none" || value == "info" || value == "debug") {
      return {};
    }
    return "Log level value not supported. Accepted values [none,info,debug]";
  };

  app.add_option("--filename", log_params.filename, "Log file output path")->capture_default_str();
  app.add_option(
         "--all_level", log_params.all_level, "Default log level for PHY, MAC, RLC, PDCP, RRC, SDAP, NGAP and GTPU")
      ->capture_default_str()
      ->check(level_check);
  app.add_option("--lib_level", log_params.lib_level, "Generic log level")->capture_default_str()->check(level_check);
  app.add_option("--config_level", log_params.config_level, "Config log level")
      ->capture_default_str()
      ->check(metric_level_check);
  app.add_option("--metrics_level", log_params.metrics_level, "Metrics log level")
      ->capture_default_str()
      ->check(metric_level_check);
  app.add_option(
         "--hex_max_size", log_params.hex_max_size, "Maximum number of bytes to print in hex (zero for no hex dumps)")
      ->capture_default_str()
      ->check(CLI::Range(0, 1024));
  app.add_option("--tracing_filename", log_params.tracing_filename, "Set to a valid file path to enable tracing")
      ->always_capture_default();

  // Post-parsing callback. This allows us to set the log level to "all" level, if no level is provided.
  app.callback([&]() {
    // Do nothing when all_level is not defined or it is defined as warning.
    if (app.count("--all_level") == 0 || log_params.all_level == "warning") {
      return;
    }

    const auto options = app.get_options();
    for (auto* option : options) {
      // Skip all_level option and unrelated options to log level.
      if (option->check_name("--all_level") || option->get_name().find("level") == std::string::npos) {
        continue;
      }

      // Do nothing if option is present.
      if (option->count()) {
        continue;
      }

      // Config and metrics loggers have only subset of levels.
      if (option->check_name("--config_level") || option->check_name("--metrics_level")) {
        if (log_params.all_level == "error") {
          option->default_val<std::string>("none");
          continue;
        }
      }

      option->default_val<std::string>(log_params.all_level);
    }
  });
}

static void configure_cli11_f1u_args(CLI::App& app, cu_up_f1u_appconfig& f1u_cfg)
{
  add_option(app,
             "--f1u_bind_addr",
             f1u_cfg.f1u_bind_addr,
             "Default local IP address interfaces bind to, unless a specific bind address is specified")
      ->check(CLI::ValidIPV4);
  add_option(app, "--udp_max_rx_msgs", f1u_cfg.udp_rx_max_msgs, "Maximum amount of messages RX in a single syscall");
}

void srsran::configure_cli11_with_cu_appconfig_schema(CLI::App& app, cu_appconfig& cu_parsed_cfg)
{
  cu_appconfig& cu_cfg = cu_parsed_cfg;

  // Logging section.
  CLI::App* log_subcmd = app.add_subcommand("log", "Logging configuration")->configurable();
  configure_cli11_log_args(*log_subcmd, cu_cfg.log_cfg);

  // F1-U section.
  CLI::App* f1u_subcmd = add_subcommand(app, "f1u", "F1-U parameters")->configurable();
  configure_cli11_f1u_args(*f1u_subcmd, cu_parsed_cfg.f1u_cfg);
}
