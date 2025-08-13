#pragma once
#include <string>
#include <cstdio>
struct Timer {
    float raceTime=0.f, lapTime=0.f, bestLap=-1.f;
    void update(float dt){ raceTime+=dt; lapTime+=dt; }
    void lapCompleted(){ if(bestLap<0.f || lapTime<bestLap) bestLap=lapTime; lapTime=0.f; }
    static std::string format(float t){
        int m=int(t)/60, s=int(t)%60, ms=int((t-int(t))*1000);
        char b[32]; std::snprintf(b,32,"%02d:%02d.%03d",m,s,ms); return b;
    }
};
