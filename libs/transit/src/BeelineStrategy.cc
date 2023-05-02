#include "BeelineStrategy.h"

BeelineStrategy::BeelineStrategy(Vector3 position, Vector3 destination)
/**
   * @brief Construct a new Beeline Strategy object
   *
   * @param position Starting position
   * @param destination End destination
   */
  : position(position), destination(destination) {}

/**
   * @brief Move toward next position
   *
   * @param entity Entity to move
   * @param dt Delta Time
   */
void BeelineStrategy::Move(IEntity* entity, double dt) {
  if (IsCompleted())
    return;

  Vector3 dir = (destination - position).Unit();

  position = position + dir * entity->GetSpeed() * dt;
  entity->SetPosition(position);
  entity->SetDirection(dir);
}

/**
   * @brief Check if the trip is completed
   *
   * @return True if complete, false if not complete
   */
bool BeelineStrategy::IsCompleted() {
  return position.Distance(destination) < 4.0;
}
