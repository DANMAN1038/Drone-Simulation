#include "SpinDecorator.h"

/**
   * @brief SpinDecorator Destructor
   */
SpinDecorator::~SpinDecorator() {
  // Delete dynamically allocated variables
  delete strategy;
}

/**
   * @brief Move the entity with the spin behavior for 4 seconds.
   * 
   * @param entity Entity to move
   * @param dt Delta Time
   */
void SpinDecorator::Move(IEntity* entity, double dt){
    if(strategy->IsCompleted() && !IsCompleted()){
        entity->Rotate(dt * 10);
        time += dt;
    } else {
        strategy->Move(entity, dt);
    }
}