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

#include "TestProtocol.h"
#include "TestOperation.h"

namespace inet {

Define_Module(TestProtocol);

bool TestProtocol::handleOperationStage(LifecycleOperation *operation, int stage, IDoneCallback *doneCallback)
{
    Enter_Method("handleOperationStage");
    if (dynamic_cast<TestNodeStartOperation *>(operation)) {
        if (stage == 0 || stage == 3)
            return true;
        else if (stage == 1) {
            scheduleAfter(3, &sendOpen);
            EV << getFullPath() << " opening connection" << endl;
        }
        else if (stage == 2) {
            scheduleAfter(2, &sendData);
            EV << getFullPath() << " sending initial data" << endl;
        }
        else
            throw cRuntimeError("Unknown stage");
        this->doneCallback = doneCallback;
        return false;
    }
    else if (dynamic_cast<TestNodeShutdownOperation *>(operation)) {
        if (stage == 0) {
            scheduleAfter(2, &sendData);
            EV << getFullPath() << " sending final data" << endl;
        }
        else if (stage == 1) {
            scheduleAfter(3, &sendClose);
            EV << getFullPath() << " closing connection" << endl;
        }
        else if (stage == 2 || stage == 3)
            return true;
        else
            throw cRuntimeError("Unknown stage");
        this->doneCallback = doneCallback;
        return false;
    }
    else
        return true;
}

void TestProtocol::initialize(int stage)
{
    connectionOpen = false;
    dataSent = false;
}

void TestProtocol::handleMessage(cMessage * message)
{
    if (message == &sendOpen) {
        connectionOpen = true;
        EV << getFullPath() << " connection open" << endl;
        doneCallback->invoke();
    }
    else if (message == &sendData) {
        dataSent = true;
        EV << getFullPath() << " data sent" << endl;
        doneCallback->invoke();
    }
    else if (message == &sendClose) {
        connectionOpen = false;
        EV << getFullPath() << " connection closed" << endl;
        doneCallback->invoke();
    }
    else
        throw cRuntimeError("Unknown message");
}

}