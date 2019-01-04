#include "..\..\..\..\..\include\kmint\pigisland\states\shark\tiredState.hpp"
#include <map>
#include <algorithm>
#include "kmint/random.hpp"
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/ActorContainer.hpp"

namespace kmint {
namespace pigisland {
tiredState::tiredState(shark & shark) :_shark(shark)
{
}

void tiredState::act()
{
	if (_shark.node().node_id() == _shark.get_resting_place()->node_id()) {
		if (_shark.get_energy() == 0) {
			_shark.actorContainer()->newRound();
			_shark.rest();
		}
		_shark.setEnergy(+ 10);
		if (_shark.get_energy() >= 100) {
			_shark.setState(shark::WANDER_STATE);
			_shark.wakeUp();
		}
	}
	else {
		auto path = _aStar.FindShortestPath(_shark.node(), *(_shark.get_resting_place()));
		_shark.node(*(path.at(0)));
	}
}

const kmint::map::map_node &find_shark_node(const kmint::map::map_graph &graph) {
	for (std::size_t i = 0; i < graph.num_nodes(); ++i) {
		if (graph[i].node_info().kind == 'K') {
			return graph[i];
		}
	}
	throw "could not find starting point";
}
}}
