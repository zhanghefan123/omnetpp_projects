/*
 * LipsinServer.cc
 *
 *  Created on: Sep 1, 2023
 *      Author: zhf
 */

#include <sstream>
#include "LipsinServer.h"
#include "inet/common/Protocol.h"
#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/projects/lipsin/lipsin_tools/LipsinTools.h"
#include "inet/projects/lipsin/lipsin_packets/LipsinHeader_m.h"
#include "inet/projects/lipsin/lipsin_table/LinkInfoTable.h"
#include "inet/projects/lipsin/const_vars/LipsinConstVar.h"

namespace inet {
    Define_Module(LipsinServer);

    void LipsinServer::initialize(int stage){
        if(stage == INITSTAGE_LOCAL){
            registerProtocol(Protocol::lipsin_app, gate("appOut"), gate("appIn"));
            this->packetLength = int(this->par("packetLength").intValue());
        }
    }

    void LipsinServer::handleMessage(cMessage *message){
        if (message->arrivedOn("appIn")){
            if(message->isPacket()){
                handlePacketFromLowerLayer(message);
            }
        }
    }

    /**
     * handle packet from lower layer
     */
    void LipsinServer::handlePacketFromLowerLayer(cMessage* message) {
        if(message->isPacket()){
            // convert the message to the packet
            auto packet = check_and_cast<Packet *>(message);

            // get the lipsin header & real link bloom filter
            // ------------------------------------------------------------------------
            auto lipsinHeader = packet->peekAtFront<LipsinHeader>();
            auto realLidsBf = lipsinHeader->getRealLidsBf();
            // ------------------------------------------------------------------------

            // print the link identifiers stored in the path header
            // ------------------------------------------------------------------------
            /*
            std::stringstream ss;
            std::string current_satellite_name = this->getParentModule()->getFullName();
            ss << current_satellite_name << " received packet, ";
            ss << "actual path: ";
            for(auto link : pathHeader->getActualLinkSet()->getInnerVector()){
                ss << "(" << link->getSrc() << "->" << link->getDest() << ")";
            }
            std::cout << LipsinTools::module_log(this, ss.str()) << std::endl;
             */
            // ------------------------------------------------------------------------

            // record the information
            // ------------------------------------------------------------------------
            std::string source = lipsinHeader->getSource();
            int bloomFilterSize = realLidsBf->getM();
            int numberOfHashFunctions = realLidsBf->getK();
            // ------------------------------------------------------------------------

            // delete the corresponding data structure
            // ------------------------------------------------------------------------
            LipsinTools::delete_lipsin_packet(packet);
            // ------------------------------------------------------------------------

            // generate a new packet and send it back to the source
            // ------------------------------------------------------------------------
            auto newPacket = generateNewPacket(source, bloomFilterSize, numberOfHashFunctions);
            this->send(newPacket, "appOut");
            // ------------------------------------------------------------------------
        }
    }



    Packet* LipsinServer::generateNewPacket(std::string sourceSatellite, int bloomFilterSize, int numberOfHashFunctions){
        // create new packet
        auto* packet = new Packet("lipsin_packet_response");
        // add payload
        addPayLoad(packet);
        // encapsulate lipsin header
        encapsulateLipsin(packet, sourceSatellite, bloomFilterSize, numberOfHashFunctions); // NOLINT
        // add protocol payload
        packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::lipsin_app); // set packet protocol
        packet->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&Protocol::lipsin_network); // next layer protocol
        return packet;
    }

    Packet* LipsinServer::encapsulateLipsin(Packet* packet, std::string destinationSatellite, int bloomFilterSize, int numberOfHashFunctions){ // NOLINT
        // initialize the seed
        int seed = 0;

        // get containing module
        cModule* containingModule = this->getParentModule();

        // get routing table
        auto* lipsinRoutingTable = dynamic_cast<LipsinRoutingTable*>(containingModule->getSubmodule("lipsinRoutingTable"));

        // create lipsin Header
        const auto& lipsinHeader = makeShared<LipsinHeader>();

        // this is the server response packet, it can only be a unicast packet
        lipsinHeader->setPacketType(LipsinConstVar::LIPSIN_UNICAST_PACKET_TYPE);

        // set the nonce
        lipsinHeader->setNonce(LipsinTools::generate_nonce());

        // get satellite id
        if(destinationSatellite.find("SAT") == std::string::npos){
            throw cRuntimeError("LipsinSender::encapsulateLipsin: destination satellite id is not valid"); // NOLINT
        }
        std::string destinationSatelliteIdStr = destinationSatellite.substr(destinationSatellite.find("SAT")+3,5);
        int destinationSatelliteId = int(std::stoi(destinationSatelliteIdStr));

        // set the packet source and packet destination
        lipsinHeader->setSource(this->getParentModule()->getFullName());
        lipsinHeader->setDestinationList(0, destinationSatelliteId);

        // create real lids bloom filter
        auto* newBloomFilter = new BloomFilter(bloomFilterSize, numberOfHashFunctions, seed);
        lipsinHeader->setRealLidsBf(newBloomFilter);

        // create virtual lids bloom filter
        auto* virtualBloomFilter = new BloomFilter(bloomFilterSize, numberOfHashFunctions, seed);
        lipsinHeader->setVirtualLidsBf(virtualBloomFilter);

        // create the path header
        auto* pathHeader = new PathHeader();
        lipsinHeader->setPathHeader(pathHeader);


        // get the corresponding routes & insert the elements into the table
        std::vector<LinkInfo*> routes = lipsinRoutingTable->getSourceRoutesByDestId(destinationSatelliteId);
        for(auto& link : routes){
            newBloomFilter->insert(link->getId());
        }

        // modify lipsin header
        packet->insertAtFront(lipsinHeader);

        return packet;
    }

    void LipsinServer::addPayLoad(Packet* packet) const{
        const auto& payload = makeShared<ByteCountChunk>(B(this->packetLength));
        packet->insertAtBack(payload);
    }

} /* namespace inet */
