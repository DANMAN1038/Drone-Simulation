#include "JumpDecorator.h"

/**
   * @brief JumpDecorator Destructor
   */
JumpDecorator::~JumpDecorator() {
  // Delete dynamically allocated variables
  delete strategy;
}

 /**
   * @brief Move the entity with the jump behavior for 4 seconds.
   * 
   * @param entity Entity to move
   * @param dt Delta Time
   */
void JumpDecorator::Move(IEntity* entity, double dt){
    if(strategy->IsCompleted() && !IsCompleted()){
        entity->Jump(dt * 10);
        time += dt;
    } else {
        strategy->Move(entity, dt);
    }
}