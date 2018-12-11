#ifndef KMINT_PIGISLAND_BOAT_HPP
#define KMINT_PIGISLAND_BOAT_HPP

#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "states/state.hpp"
#include <map>

namespace kmint {
namespace pigisland {

class boat : public play::map_bound_actor {
public:
	enum STATE_NAMES {
		WANDER_STATE,
		REPAIR_STATE
	};
  boat(kmint::map::map_graph &g);
  ui::drawable const &drawable() const override { return drawable_; }
  bool incorporeal() const override { return false; }
  scalar radius() const override { return 16.0; }
  void act(delta_time dt) override;

private:
  play::image_drawable drawable_;
  //[[maybe_unused]] map::map_graph *map_;
  delta_time t_since_move_{};

  state* currentState;
  std::map<STATE_NAMES, std::unique_ptr<state>> States;
  std::vector<const kmint::map::map_node*> path;

  void RegisterStates();
};

} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_BOAT_HPP */
