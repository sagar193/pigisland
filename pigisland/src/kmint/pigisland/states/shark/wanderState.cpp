#include "..\..\..\..\..\include\kmint\pigisland\states\shark\wanderState.hpp"
#include <map>
#include <algorithm>
#include "kmint/random.hpp"
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"

namespace kmint {
namespace pigisland {
wanderState::wanderState(shark & shark) :_shark(shark)
{
}

void wanderState::act()
{
	_shark.node(random_adjacent_node(_shark.node()));
}
}}