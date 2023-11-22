//
// Copyright (C) 2013 OpenSim Ltd.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#include "TestRadio.h"
#include "TestOperation.h"

namespace inet {

Define_Module(TestRadio);

bool TestRadio::handleOperationStage(LifecycleOperation *operation, int stage, IDoneCallback *doneCallback)
{
    Enter_Method("handleOperationStage");
    if (dynamic_cast<TestNodeStartOperation *>(operation)) {
        if (stage == 0) {
            scheduleAfter(1, &turnOnTransmitter);
            EV << getFullPath() << " turning on transmitter" << endl;
        }
        else if (stage == 1) {
            scheduleAfter(2, &turnOnReceiver);
            EV << getFullPath() << " turning on receiver" << endl;
        }
        else if (stage == 2 || stage == 3)
            return true;
        else
            throw cRuntimeError("Unknown stage");
        this->doneCallback = doneCallback;
        return false;
    }
    else if (dynamic_cast<TestNodeShutdownOperation *>(operation)) {
        if (stage == 0 || stage == 3)
            return true;
        else if (stage == 1) {
            scheduleAfter(2, &turnOffReceiver);
            EV << getFullPath() << " turning off receiver" << endl;
        }
        else if (stage == 2) {
            scheduleAfter(1, &turnOffTransmitter);
            EV << getFullPath() << " turning off transmitter" << endl;
        }
        else
            throw cRuntimeError("Unknown stage");
        this->doneCallback = doneCallback;
        return false;
    }
    else
        return true;
}

void TestRadio::initialize(int stage)
{
    receiverTurnedOn = false;
    transmitterTurnedOn = false;
}

void TestRadio::handleMessage(cMessage * message)
{
    if (message == &turnOnTransmitter) {
        transmitterTurnedOn = true;
        EV << getFullPath() << " transmitter turned on" << endl;
        doneCallback->invoke();
    }
    else if (message == &turnOnReceiver) {
        receiverTurnedOn = true;
        EV << getFullPath() << " receiver turned on" << endl;
        doneCallback->invoke();
    }
    else if (message == &turnOffTransmitter) {
        transmitterTurnedOn = false;
        EV << getFullPath() << " transmitter turned off" << endl;
        doneCallback->invoke();
    }
    else if (message == &turnOffReceiver) {
        receiverTurnedOn = false;
        EV << getFullPath() << " receiver turned off" << endl;
        doneCallback->invoke();
    }
    else
        throw cRuntimeError("Unknown message");
}

}