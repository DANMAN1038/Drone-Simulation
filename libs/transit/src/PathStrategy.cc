#include "PathStrategy.h"

/**
   * @brief Construct a new PathStrategy Strategy object
   *
   * @param path the path to follow
   */
PathStrategy::PathStrategy(std::vector<std::vector<float>> p)
  : path(p), index(0) {}

/**
   * @brief Move toward next position in the path
   *
   * @param entity Entity to move
   * @param dt Delta Time
   */
void PathStrategy::Move(IEntity* entity, double dt) {
  if (IsCompleted())
    return;

  Vector3 vi(path[index][0], path[index][1], path[index][2]);
  Vector3 dir = (vi - entity->GetPosition()).Unit();

  entity->SetPosition(entity->GetPosition() + dir*entity->GetSpeed()*dt);
  entity->SetDirection(dir);

  if (entity->GetPosition().Distance(vi) < 4)
    index++;
}

/**
   * @brief Check if the trip is completed by seeing if index 
   *        has reached the end of the path
   *
   * @return True if complete, false if not complete
   */
bool PathStrategy::IsCompleted() {
  return index >= path.size();
}
