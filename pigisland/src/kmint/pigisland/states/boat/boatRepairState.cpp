#include "..\..\..\..\..\include\kmint\pigisland\states\boat\boatRepairState.hpp"
#include <map>
#include <algorithm>
#include "kmint/random.hpp"
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include <iostream> 

namespace kmint {
namespace pigisland {

	boatRepairState::boatRepairState(kmint::pigisland::boat& boat) :_boat(boat)
	{
		for (int i = 0; i < 3; i++) {
			auto& test = find_node_of_kind(_boat.graph(), '1' + i);
			_moorings[1+i] = &test;
			_mooringsEffectiveness[1 + i] = 200;
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
		int repair = 0;
		if (_goal->node_info().kind == '1') {
			repair = random_int(30, 51);
			_boat.durability(repair);
			_mooringsEffectiveness.at(1) = (_mooringsEffectiveness.at(1) + repair) / 2;
			_goal = nullptr;
			std::cout << "mooring 1 repaired " << repair << " durability \n";
		}
		else if (_goal->node_info().kind == '2') {
			repair = random_int(20, 101);
			_boat.durability(repair);
			_mooringsEffectiveness.at(2) = (_mooringsEffectiveness.at(2) + repair) / 2;
			_goal = nullptr;
			std::cout << "mooring 2 repaired " << repair << " durability \n";
		}
		else if (_goal->node_info().kind == '3') {
			_boat.durability(50);
			_mooringsEffectiveness.at(3) = (_mooringsEffectiveness.at(3) + 50) / 2;
			_goal = nullptr;
			std::cout << "mooring 3 repaired 50 durability \n";
		}
		else {
			throw "something went wrong repairing boat";
		}
		_boat.setState(boat::WANDER_STATE);
		printMooringEffectiveness();
	}

	void boatRepairState::pickGoal() {
		int totalEffectiveness = 0;
		for (auto it = _mooringsEffectiveness.begin(); it != _mooringsEffectiveness.end(); it++) {
			totalEffectiveness += it->second;
		}
		int choice = random_int(0, totalEffectiveness);
		int lastValue = 0;
		for (int i = 1; i < _mooringsEffectiveness.size()+1; i++) {
			if (choice < _mooringsEffectiveness.at(i)+lastValue) {
				_goal = _moorings.at(i);
				return;
			}
			else {
				lastValue += _mooringsEffectiveness.at(i);
			}
		}
	}

	void boatRepairState::printMooringEffectiveness() {
		std::cout << "mooring effectiveness:";
		int i = 0;
		for (auto it = _mooringsEffectiveness.begin(); it != _mooringsEffectiveness.end(); it++) {
			std::cout << " (" << i << ") " << it->second;
			i++;
		}
		std::cout << "\n";

	}
}
}