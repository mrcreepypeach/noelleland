#ifndef TIMER
#define TIMER

#include "raylib.h"

#include <string>
#include <vector>

struct timer {
    static std::vector<timer*> allTimers;
    double lastTime = GetTime();
    double timeToWait;

    bool complete = false;
    
    std::string name;

    timer(double timewait, std::string timerName){
        timeToWait = timewait;
        name = timerName;

        allTimers.push_back(this);
    }

    void update(){
        if ((GetTime() - lastTime) >= timeToWait){
            complete = true;
        }
    }
};

#endif