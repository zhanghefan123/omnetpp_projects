#include "GlobalModule.h"
#include <fstream>
namespace inet{
    Define_Module(GlobalModule);

    void GlobalModule::initialize(int stage){
        switch(stage){
            case 1:{
                getQtOrCmd();
                break;
            }
            default:{
                break;
            }
        }
        this->start = 60;
    }

    void GlobalModule::getQtOrCmd(){
        cEnvir* envir = this->getSimulation()->getEnvir();
        if(envir->isGUI()){
            this->startFromQtEnv = true;
        } else {
            this->startFromQtEnv = false;
        }
    }

    void GlobalModule::update_final_not_hello_packet_time(){
        this->final_not_hello_packet_time = omnetpp::simTime().dbl();
    }

    void GlobalModule::update_routing_table_rebuild_time(){
        this->routing_table_rebuild_time = omnetpp::simTime().dbl();
    }

    void GlobalModule::update_ospf_consumption_in_bytes(double packet_size){
        double current_time = omnetpp::simTime().dbl();
        if((current_time > start)){
            this->ospf_consumption += packet_size;
        }
    }

    void GlobalModule::output_result(){
        std::ofstream output_file;
        output_file.open("final_result.txt", std::ios::app);
        output_file << "ospf_consumption (in Mbytes): " << this->ospf_consumption << " bytes" << std::endl;
        output_file << "routing table rebuild time: " << this->routing_table_rebuild_time - this->start << " s" << std::endl;
        output_file.close();
    }

    void GlobalModule::finish(){
        this->output_result();
    }
}
