#include "AstarStrategy.h"
#include "routing/astar.h"

/**
   * @brief Construct a new Astar Strategy object
   *
   * @param position Current position
   * @param destination End destination
   * @param graph Graph/Nodes of the map
   */

AstarStrategy::AstarStrategy(Vector3 pos, Vector3 des,
                             const routing::IGraph* g) {
  std::vector<float> start = {pos[0], pos[1], pos[2]};
  std::vector<float> end   = {des[0], des[1], des[2]};
  path = g->GetPath(start, end, AStar::Default());
}
