#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/states/boat/boatWanderState.hpp"
#include "kmint/pigisland/states/boat/boatRepairState.hpp"

namespace kmint {
namespace pigisland {

boat::boat(kmint::map::map_graph &g)
    : play::map_bound_actor{g, find_random_mooring_place(g)},
      drawable_{*this, boat_image()} /*, map_{&g}*/ 
{
	RegisterStates();
	setState(WANDER_STATE);
	_durability = 100;
}

void boat::act(delta_time dt) {
  t_since_move_ += dt;
  if (to_seconds(t_since_move_) >= waiting_time(node())) {
	  currentState->act();
	  /*
	  node(random_adjacent_node(node()));
	  */
    t_since_move_ = from_seconds(0);
  }
}

void boat::RegisterStates() {
	States[boat::STATE_NAMES::WANDER_STATE] = std::make_unique<boatWanderState>(*this);
	States[boat::STATE_NAMES::REPAIR_STATE] = std::make_unique<boatRepairState>(*this);
}

void boat::setState(STATE_NAMES state) {
	currentState = States[state].get();
}

} // namespace pigisland
} // namespace kmint
