#include "..\..\..\..\..\include\kmint\pigisland\states\boat\boatWanderState.hpp"
#include <map>
#include <algorithm>
#include "kmint/random.hpp"
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/node_algorithm.hpp"

namespace kmint {
namespace pigisland {

boatWanderState::boatWanderState(kmint::pigisland::boat& boat) :_boat(boat)
{
}

void boatWanderState::act()
{
	_boat.node(random_adjacent_node(_boat.node()));
	_boat.durability(-1);
}

}
}