//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/physicallayer/wireless/common/analogmodel/packetlevel/ScalarTransmission.msg.
//

#ifndef __INET__PHYSICALLAYER_SCALARTRANSMISSION_M_H
#define __INET__PHYSICALLAYER_SCALARTRANSMISSION_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0600
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

// dll export symbol
#ifndef INET_API
#  if defined(INET_EXPORT)
#    define INET_API  OPP_DLLEXPORT
#  elif defined(INET_IMPORT)
#    define INET_API  OPP_DLLIMPORT
#  else
#    define INET_API
#  endif
#endif


namespace inet {
namespace physicallayer {


}  // namespace physicallayer
}  // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/Units_m.h" // import inet.common.Units

#include "inet/physicallayer/wireless/common/base/packetlevel/FlatTransmissionBase_m.h" // import inet.physicallayer.wireless.common.base.packetlevel.FlatTransmissionBase

// cplusplus {{
#include "inet/physicallayer/wireless/common/analogmodel/packetlevel/ScalarTransmission.h"
// }}


namespace inet {
namespace physicallayer {


}  // namespace physicallayer
}  // namespace inet


namespace omnetpp {

template<> inline inet::physicallayer::ScalarTransmission *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::physicallayer::ScalarTransmission*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __INET__PHYSICALLAYER_SCALARTRANSMISSION_M_H
