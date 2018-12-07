#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"

namespace kmint {
namespace pigisland {

shark::shark(kmint::map::map_graph &g)
    : play::map_bound_actor{g, find_shark_resting_place(g)},
      drawable_{*this, shark_image()}, map_{&g}, resting_place_(&node()) {}

void shark::act(delta_time dt) {
  t_since_move_ += dt;
  if (to_seconds(t_since_move_) >= waiting_time(node())) {
    node(random_adjacent_node(node()));
    t_since_move_ = from_seconds(0);
  }
}

} // namespace pigisland
} // namespace kmint
