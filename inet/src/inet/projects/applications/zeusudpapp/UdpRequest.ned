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
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package inet.projects.applications.zeusudpapp;

import inet.applications.contract.IApp;

//
// request response client.
//
// This module sends one "packet request" to serverAddress:serverPort at time startTime
// and receives stream from ~UdpResponse.
//
simple UdpRequest like IApp
{
    parameters:
        @display("i=block/app");
        @lifecycleSupport;
        int localPort = default(-1);
        double sendInterval @unit(s) = default(1s); // the send interval only related with the client
        string serverAddress;
        int serverPort;
        double startTime @unit(s) = default(1s);
        double stopTime @unit(s) = default(1s);
        string outputDir = default("./");
        string requestPacketName = default("udpRequestPacket");
        double stopOperationExtraTime @unit(s) = default(-1s);    // extra time after lifecycle stop operation finished
        double stopOperationTimeout @unit(s) = default(2s);    // timeout value for lifecycle stop operation
        string transmissionPattern = default("PUSH"); // the transmission pattern can be PUSH or PULL
        int packetLength = default(1000);
        @signal[packetReceived](type=inet::Packet);
 
    gates:
        input socketIn @labels(UdpControlInfo/up);
        output socketOut @labels(UdpControlInfo/down);
}
