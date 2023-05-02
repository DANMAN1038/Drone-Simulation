#include "Robot.h"

/**
   * @brief Constructor
   * @param obj JSON object containing the robot's information
   */
Robot::Robot(JsonObject &obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};
  speed = obj["speed"];
  available = true;
}

/**
   * @brief Gets the robot's details
   * @return The robot's details
   */
JsonObject Robot::GetDetails() const { return details; }

/**
   * @brief Sets the robot's availability
   * @param choice The new availability of the robot
   */
void Robot::SetAvailability(bool choice) { available = choice; }

/**
   * @brief Rotates the robot
   * @param angle The angle by which the robot should be rotated
   */
void Robot::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}
