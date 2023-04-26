#include "DroneLogger.h"
#include <mutex> 
DroneLogger* DroneLogger::pinstance_ = nullptr;
DroneLogger::DroneLogger(){
    this->pinstance_ = nullptr;
};
DroneLogger* DroneLogger::GetInstance()
{
    if (pinstance_ == nullptr){
        pinstance_ = new DroneLogger();
    }
    return pinstance_;
};
int counter = 0;
void DroneLogger::logDrone(IEntity * drone){
    Drone* drone_test = dynamic_cast<Drone*>(drone);
    if(drone_test == nullptr){
        return;
    }
    std::ofstream file("example.csv", std::ios::app);

    if (!file.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return;
    }
    if(counter == 0){
        file << "Dir X" << "," << "Dir Y" << "," << "Dir Z" << "," << "Speed" << "," << "Color" << std::endl;
    }
    counter++;

    if(counter == 1000 && drone_test->GetFinalDestination() != nullptr){
        file << drone_test->GetDirection().x << ", " << drone_test->GetDirection().y << ", " << drone_test->GetDirection().z << ", " << drone_test->GetSpeed() << ", " << drone_test->GetColor()<<  std::endl;
        counter = 1;
    }
    file.close();
    return;
}
