#include "DroneLogger.h"
#include <mutex> 
/**
 * @brief A singleton class that logs the data of a drone and robot
 */
DroneLogger* DroneLogger::pinstance_ = nullptr;
DroneLogger::DroneLogger(){
    this->pinstance_ = nullptr;
};
/**
     * @brief Returns the instance of a drone
     * @return The instance of the drone
     */
DroneLogger* DroneLogger::GetInstance()
{
    if (pinstance_ == nullptr){
        pinstance_ = new DroneLogger();                    // Gets a single instance
    }
    return pinstance_;
};
int counter = 0;                                           // counter used to track updates
int num_rows = 1;                                          // num rows for excel calculations
bool lastline = false;                                     // Makes sure to write last line only once
int robotrow = 0;                                         // What row in excel the robot was picked up
bool pickup = false;  
                                     // Make sure the value of robot_row isn't changed
/**
    * @brief Logs the data of a drone.
    * @param drone A pointer to the drone entity.
    */
void DroneLogger::logDrone(IEntity * drone){
    Drone* drone_test = dynamic_cast<Drone*>(drone);
    if(drone_test == nullptr){
        return;                                                       // Checks if Ientity is a drone
    }
    if(counter == 0){
        std::ofstream file("data.csv", std::ios::trunc);
        if (!file.is_open()) {
            std::cerr << "Failed to open file!" << std::endl;
            return;                                                       // Gets rid of what was in the file and writes the first line
        }
        file << "Dir X" << "," << "Dir Y" << "," << "Dir Z" << ",";
        file << "Pos X" << "," << "Pos Y" << "," << "Pos Z" << ",";  
        file << "Speed" << "," << "Color" << std::endl;
        file.close();
    }
    counter++;

    if(counter == 750){                                                     // Only writes every 750 updates
        if(drone_test->GetFinalDestination() != nullptr){                    // While drone hasn't gone to the final destination
            std::ofstream file("data.csv", std::ios::app);                
            if(!file.is_open()) {
                std::cerr << "Failed to open file!" << std::endl;
                return;
            }
            num_rows++;
            if(drone_test->Getpickedup() == true && pickup == false){             // checks if robot was picked up
                robotrow = num_rows;
                pickup = true;
            }
            file << drone_test->GetDirection().x << ", " << drone_test->GetDirection().y << ", " << drone_test->GetDirection().z << ", "; 
            file << drone_test->GetPosition().x << ", " << drone_test->GetPosition().y << ", " << drone_test->GetPosition().z << ", ";            // writes values to csv file
            file << drone_test->GetSpeed() << ", " << drone_test->GetColor()<<  std::endl;
            counter = 1;
            file.close();
        }
        else if(lastline == false){
            std::ofstream file("data.csv", std::ios::app);
            if(!file.is_open()) {                                                            // Makes sure the last line is printed once 
                std::cerr << "Failed to open file!" << std::endl;
                return;
            }   
            file << "Total distance" << "," << "" <<"," <<  "Robot distance" << "," << "" << "," << "Average speed" << std::endl;
            file << "=SUM(SQRT((D3:D" << num_rows << "-" << "D2:D"<< num_rows-1 << ")^2+";  
            file << "(E3:E" << num_rows << "-" << "E2:E"<< num_rows-1 << ")^2+";                                                                   // Calculates for total distance in excel
            file << "(F3:F" << num_rows << "-" << "F2:F"<< num_rows-1 << ")^2))" << ",";

            file << "=SUM(SQRT((D"<< robotrow << ":D" << num_rows << "-" << "D"<< robotrow -1 << ":D"<< num_rows-1 << ")^2+";  
            file << "(E"<< robotrow << ":E" << num_rows << "-" << "E"<< robotrow -1 << ":E"<< num_rows-1 << ")^2+";
            file << "(F"<< robotrow << ":F" << num_rows << "-" << "F"<< robotrow -1 << ":F"<< num_rows-1 << ")^2))" << ",";                     // Calculates total distance with robot in excel
            
            file << "=AVERAGE(G2:G" << num_rows << ")" << std::endl;                // Calculates average speed in excel.
       
            lastline = true;
            file.close();
        }
    }
    return;
}
