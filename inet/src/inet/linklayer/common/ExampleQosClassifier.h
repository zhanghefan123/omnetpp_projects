//
// Copyright (C) 2010 Alfonso Ariza
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
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//

#ifndef __INET_EXAMPLEQOSCLASSIFIER_H
#define __INET_EXAMPLEQOSCLASSIFIER_H

#include "inet/common/IProtocolRegistrationListener.h"

namespace inet {

/**
 * An example packet classifier based on the UDP/TCP port number.
 */
class INET_API ExampleQosClassifier : public cSimpleModule, public DefaultProtocolRegistrationListener
{
  protected:
    virtual int getUserPriority(cMessage *msg);
    virtual void handleRegisterService(const Protocol& protocol, cGate *gate, ServicePrimitive servicePrimitive) override;
    virtual void handleRegisterProtocol(const Protocol& protocol, cGate *gate, ServicePrimitive servicePrimitive) override;

  public:
    ExampleQosClassifier() {}
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

} // namespace inet

#endif

