#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/states/shark/wanderState.hpp"
#include "kmint/pigisland/states/shark/fleeState.hpp"
#include "kmint/pigisland/states/shark/huntState.hpp"
#include "kmint/pigisland/states/shark/tiredState.hpp"

///todo: signaal afgeven als haai bij resting place is
///todo: biggen opeten

namespace kmint {
namespace pigisland {

	shark::shark(kmint::map::map_graph &g)
		: play::map_bound_actor{ g, find_shark_resting_place(g) },
		drawable_{ *this, shark_image() }, map_{ &g }, resting_place_(&node())
{
	RegisterStates();
	setState(WANDER_STATE);
	_energy = 100;
}

void shark::act(delta_time dt) {
  t_since_move_ += dt;
  if (to_seconds(t_since_move_) >= waiting_time(node())) {
	  if (_energy == 0) {
		  setState(STATE_NAMES::TIRED_STATE);
	  }
	  currentState->act();
    t_since_move_ = from_seconds(0);
  }
}

void shark::RegisterStates() {
	States[shark::STATE_NAMES::FLEE_STATE] = std::make_unique<fleeState>(*this);
	States[shark::STATE_NAMES::HUNT_STATE] = std::make_unique<huntState>(*this);
	States[shark::STATE_NAMES::TIRED_STATE] = std::make_unique<tiredState>(*this);
	States[shark::STATE_NAMES::WANDER_STATE] = std::make_unique<wanderState>(*this);
}

void shark::setState(STATE_NAMES state) {
	currentState = States[state].get();
}

} // namespace pigisland
} // namespace kmint
