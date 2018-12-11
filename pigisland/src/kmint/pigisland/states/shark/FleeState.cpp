#include "..\..\..\..\..\include\kmint\pigisland\states\shark\fleeState.hpp"
#include <map>
#include <algorithm>
#include "kmint/random.hpp"
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/pigisland/shark.hpp"

namespace kmint {
namespace pigisland {

fleeState::fleeState(kmint::pigisland::shark & shark) :_shark(shark)
{
}

void fleeState::act()
{
}
}}