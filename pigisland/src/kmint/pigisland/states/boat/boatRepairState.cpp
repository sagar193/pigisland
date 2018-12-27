#include "..\..\..\..\..\include\kmint\pigisland\states\boat\boatRepairState.hpp"
#include <map>
#include <algorithm>
#include "kmint/random.hpp"
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/node_algorithm.hpp"

namespace kmint {
namespace pigisland {

	boatRepairState::boatRepairState(kmint::pigisland::boat& boat) :_boat(boat)
	{
		for (int i = 0; i < 3; i++) {
			auto& test = find_node_of_kind(_boat.graph(), '1' + i);
			_moorings[i] = &test;
			_mooringsEffectiveness[i] = 200;
		}
		_goal = nullptr;
	}

	void boatRepairState::act()
	{
		if (_goal == nullptr) {
			pickGoal();
		}

		if (_boat.node().node_id() == _goal->node_id()) {
			repair();
		}
		else {
			auto path = _astar.FindShortestPath(_boat.node(), *_goal);
			_boat.node(*(path.at(0)));
			_boat.durability();
		}
	}

	void boatRepairState::repair() {
		if (_goal->node_info().kind == '1') {
			_boat.durability(random_int(30, 51));
			_goal = nullptr;
		}
		else if (_goal->node_info().kind == '2') {
			_boat.durability(random_int(20, 101));
			_goal = nullptr;

		}
		else if (_goal->node_info().kind == '3') {
			_boat.durability(50);
			_goal = nullptr;
		}
		else {
			throw "something went wrong repairing boat";
		}
	}

	void boatRepairState::pickGoal() {

	}
}
}