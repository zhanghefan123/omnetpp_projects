//
// Copyright (C) 2005 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#ifndef _SATTOSAT_H
#define _SATTOSAT_H

#include "inet/common/INETDefs.h"
#include "inet/common/misc/ThruputMeteringChannel.h"
#include "SatMobility.h"


/**
 * A cDatarateChannel extended with throughput calculation. Values
 * get displayed on the link, using the connection's "t=" display
 * string tag.
 *
 * The display can be customized with the "format" attribute.
 * In the format string, the following characters will get expanded:
 *   - 'N': number of packets
 *   - 'V': volume (in bytes)
 *   - 'p': current packet/sec
 *   - 'b': current bandwidth
 *   - 'u': current channel utilization (%)
 *   - 'P': average packet/sec on [0,now)
 *   - 'B': average bandwidth on [0,now)
 *   - 'U': average channel utilization (%) on [0,now)
 * Other characters are copied verbatim.
 *
 * "Current" actually means the last measurement interval, which is
 * 10 packets or 0.1s, whichever comes first.
 *
 * PROBLEM: display only gets updated if there's traffic! (For example, a
 * high pk/sec value might stay displayed even when the link becomes idle!)
 */
class INET_API SatToSat : public ThruputMeteringChannel, public cListener
{
private:
    cModule *host = nullptr; // for subscribe the link signal
    bool initialized = false;
protected:
    /// cListener method
    virtual void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details) override;

  public:
    /**
     * Constructor.
     */
    explicit SatToSat(const char *name = nullptr): ThruputMeteringChannel(name),cListener(),initialized(false){}

    /**
     * Copy constructor.
     */
//    ThruputMeteringChannel(const ThruputMeteringChannel& ch);

    /**
     * Destructor.
     */
    ~SatToSat() override= default;

    /**
     * Assignment
     */
//    ThruputMeteringChannel& operator=(const ThruputMeteringChannel& ch);

    /**
     * Creates and returns an exact copy of this object.
     * See cObject for more details.
     */
//    virtual ThruputMeteringChannel *dup() const {return new ThruputMeteringChannel(*this);}

    /**
     * Add parameters and initialize the stat variables
     */
    virtual void initialize() override;
    double getDistance();

    /**
     * Adds statistics and live display to the channel.
     */
    virtual cChannel::Result processMessage(cMessage *msg, const SendOptions& options, simtime_t t) override;
};

#endif // ifndef _SATTOSAT_H

