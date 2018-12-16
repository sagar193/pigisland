#include "..\..\..\..\..\include\kmint\pigisland\states\shark\fleeState.hpp"
#include <map>
#include <algorithm>
#include "kmint/random.hpp"
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"

namespace kmint {
namespace pigisland {

fleeState::fleeState(kmint::pigisland::shark & shark) :_shark(shark)
{
	_fleeCounter = 10;
}

void fleeState::act()
{
	if (_fleeCounter == 0) {
		_shark.setState(shark::WANDER_STATE);
		_fleeCounter = 10;
		return;
	}
	_fleeCounter--;
	_shark.node(random_adjacent_node(_shark.node()));
}
}}