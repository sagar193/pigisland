#include "..\..\..\..\..\include\kmint\pigisland\states\shark\huntState.hpp"
#include <map>
#include <algorithm>
#include "kmint/random.hpp"
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/pigisland/shark.hpp"

namespace kmint {
namespace pigisland {
huntState::huntState(shark & shark) :_shark(shark)
{
}

void huntState::act()
{
}
}}