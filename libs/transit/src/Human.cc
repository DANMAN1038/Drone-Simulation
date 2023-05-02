#define _USE_MATH_DEFINES
#include "Human.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"

/**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
Human::Human(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];
}

/**
   * @brief Destroy the Human object
   */
Human::~Human() {
  // Delete dynamically allocated variables
  delete graph;
}

/**
    * @brief Create a new destination for the Human object to adventure to
    */
void Human::CreateNewDestination() {
    destination = {Random(-1400, 1500), position.y, Random(-800, 800)};
    toDestination = new AstarStrategy(position, destination, graph);
}

/**
   * @brief Updates the drone's position
   * @param dt Delta time
   * @param scheduler Vector containing all the entities in the system
   */
void Human::Update(double dt, std::vector<IEntity*> scheduler) {
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