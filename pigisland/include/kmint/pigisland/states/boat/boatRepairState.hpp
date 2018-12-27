#pragma once
#include "../state.hpp"
#include <map>
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "../../aStar.hpp"

namespace kmint {
namespace pigisland {
class boat;
class boatRepairState : public state
{
public:
	boatRepairState(kmint::pigisland::boat& boat);
	void act() override;

	boatRepairState() = default;
private:
	kmint::pigisland::boat& _boat;
	aStar _astar;
	std::map<int, const kmint::map::map_node*> _moorings;
	std::map<int, int> _mooringsEffectiveness;
	const kmint::map::map_node* _goal;


	void repair();
	void pickGoal();
};
}
}