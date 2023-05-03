#ifndef DroneLogger_H
#define DroneLogger_H

#include "Drone.h"
#include <fstream>
#include <iostream>
#include <string>
#include <thread>         
#include <mutex> 
class DroneLogger {
public:
    static DroneLogger* GetInstance();
    void logDrone(IEntity * drone);
protected:
    DroneLogger();
    DroneLogger(const DroneLogger&) = delete;
    DroneLogger& operator=(const DroneLogger&) = delete;
private:
    static DroneLogger* pinstance_;
};
#endif 