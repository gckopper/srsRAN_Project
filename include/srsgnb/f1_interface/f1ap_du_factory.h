#ifndef SRSGNB_F1AP_DU_FACTORY_H
#define SRSGNB_F1AP_DU_FACTORY_H

#include "srsgnb/f1_interface/f1ap_du.h"
#include "srsgnb/support/timers.h"
#include <memory>

namespace srsgnb {
namespace srs_du {

/// Creates an instance of an F1AP DU interface, notifying outgoing packets on the specified listener object.
std::unique_ptr<f1_interface> create_f1ap(timer_manager& timer_db, f1c_message_handler& f1c_pdu_handler_);

} // namespace srs_du
} // namespace srsgnb

#endif // SRSGNB_F1AP_DU_FACTORY_H
