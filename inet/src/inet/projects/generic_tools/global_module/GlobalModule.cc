#include "GlobalModule.h"
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
    }

    void GlobalModule::getQtOrCmd(){
        cEnvir* envir = this->getSimulation()->getEnvir();
        if(envir->isGUI()){
            this->startFromQtEnv = true;
        } else {
            this->startFromQtEnv = false;
        }
    }
}
