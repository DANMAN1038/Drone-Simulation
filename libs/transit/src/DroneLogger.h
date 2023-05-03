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
/**
     * @brief Returns the instance of a drone
     * @return The instance of the drone
     */
    static DroneLogger* GetInstance();
    /**
    * @brief Logs the data of a drone.
    * @param drone A pointer to the drone entity.
    */
    void logDrone(IEntity * drone);
protected:
/**
    * @brief constructor for logging drone
    */
    DroneLogger();
/**
    * @brief destructor for dronelogger object
    */
    DroneLogger(const DroneLogger&) = delete;
/**
    * @brief destructor for dronelogger object
    */
    DroneLogger& operator=(const DroneLogger&) = delete;
private:
    static DroneLogger* pinstance_;
};
#endif 