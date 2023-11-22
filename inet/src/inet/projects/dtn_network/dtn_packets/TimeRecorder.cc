#include "TimeRecorder.h"
namespace inet{
    double TimeRecorder::getTime() const{
        return this->time;
    }
    void TimeRecorder::setTime(double timeTmp){
        this->time = timeTmp;
    }
}