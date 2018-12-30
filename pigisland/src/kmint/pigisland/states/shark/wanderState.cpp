#include "..\..\..\..\..\include\kmint\pigisland\states\shark\wanderState.hpp"
#include <map>
#include <algorithm>
#include "kmint/random.hpp"
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/node_algorithm.hpp"

namespace kmint {
namespace pigisland {
wanderState::wanderState(shark & shark) :_shark(shark)
{
}

void wanderState::act()
{
	_shark.setEnergy(-1);
	_shark.node(random_adjacent_node(_shark.node()));
	for (auto i = _shark.begin_perceived(); i != _shark.end_perceived(); i++) {
		kmint::play::actor *ptr = &(*i);
		if (auto p = dynamic_cast<kmint::pigisland::boat*>(ptr); p)
		{
			_shark.setState(shark::FLEE_STATE);
			return;
		}
	}
	if (_shark.begin_perceived() != _shark.end_perceived()) {
		_shark.setState(shark::HUNT_STATE);
	}
}
}}