#define _USE_MATH_DEFINES
#include "Helicopter.h"

#include <cmath>
#include <limits>

#include "BeelineStrategy.h"

/**
   * @brief Helicopter are created with a name
   * @param obj JSON object containing the drone's information
   */
Helicopter::Helicopter(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];
}

/**
   * @brief Destroy the Helicopter object
   */
Helicopter::~Helicopter() {
  // Delete dynamically allocated variables
  delete graph;
}

/**
  * @brief Create a new destination for the helicopter to adventure to
*/
void Helicopter::CreateNewDestination() {
    destination = {Random(-1400, 1500), position.y, Random(-800, 800)};
    toDestination = new BeelineStrategy(position, destination);
}

/**
   * @brief Rotates the drone
   * @param angle The angle by which the drone should be rotated
   */
void Helicopter::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}

/**
   * @brief Updates the drone's position
   * @param dt Delta time
   * @param scheduler Vector containing all the entities in the system
   */
void Helicopter::Update(double dt, std::vector<IEntity*> scheduler) {
    if(toDestination) {
        if(toDestination->IsCompleted()) {
            CreateNewDestination();
        } else {
            toDestination->Move(this, dt);
        }
    } else {
        CreateNewDestination();
    }
}