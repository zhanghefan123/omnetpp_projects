#ifndef __INET_TIME_RECORDER_H
#define __INET_TIME_RECORDER_H
namespace inet{
    class TimeRecorder{
    public:
        double time;
        double getTime() const;
        void setTime(double timeTmp);
    };
}
#endif // ifndef __INET_TIME_RECORDER_H