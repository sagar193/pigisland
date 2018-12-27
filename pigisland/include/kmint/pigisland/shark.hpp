#ifndef KMINT_PIGISLAND_SHARK_HPP
#define KMINT_PIGISLAND_SHARK_HPP

#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "states/State.hpp"
#include <map>

namespace kmint {
namespace pigisland {
class shark : public play::map_bound_actor {
public:
	enum STATE_NAMES {
		WANDER_STATE,
		HUNT_STATE,
		FLEE_STATE,
		TIRED_STATE
	};

  shark(kmint::map::map_graph &g);
  ui::drawable const &drawable() const override { return drawable_; }
  bool incorporeal() const override { return false; }
  scalar radius() const override { return 16.0; }
  void act(delta_time dt) override;
  bool perceptive() const override { return true; };
  scalar range_of_perception() const override { return 100.0f; };
  kmint::map::map_graph *_g() { return map_; };
  const kmint::map::map_node* get_resting_place() { return resting_place_; };
  const int get_energy() { return _energy; };
  void setEnergy(int energy) { _energy = energy; };

  void setState(STATE_NAMES state);
private:
  play::image_drawable drawable_;
  map::map_graph *map_;
  map::map_node const *resting_place_;
  delta_time t_since_move_{};
  int _energy;

  state* currentState;
  std::map<STATE_NAMES, std::unique_ptr<state>> States;
  std::vector<const kmint::map::map_node*> path;

  void RegisterStates();
};

} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_SHARK_HPP */
