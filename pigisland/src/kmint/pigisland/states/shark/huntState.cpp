#include "..\..\..\..\..\include\kmint\pigisland\states\shark\huntState.hpp"
#include <map>
#include <algorithm>
#include "kmint/random.hpp"
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/node_algorithm.hpp"

namespace kmint {
namespace pigisland {
huntState::huntState(shark & shark) :_shark(shark)
{}

void huntState::act()
{
	_shark.setEnergy(-1);

	for (auto i = _shark.begin_collision(); i != _shark.end_collision(); ++i) {
		play::actor *ptr = &(*i);
		if (auto p = dynamic_cast<pig*>(ptr); p)
		{
			p->die();
		}
	}

	pig* closestPig;
	double closestPigDistance = 99999;

	//get closest pig
	for (auto i = _shark.begin_perceived(); i != _shark.end_perceived(); ++i) {
		kmint::play::actor *ptr = &(*i);
		if (auto b = dynamic_cast<kmint::pigisland::boat*>(ptr); b)
		{
			_shark.setState(shark::FLEE_STATE);
			return;
		}
		else if (auto p = dynamic_cast<kmint::pigisland::pig*>(ptr); p)
		{
			double distance = calculateDistance(p);
			if (closestPigDistance > distance) {
				closestPigDistance = distance;
				closestPig = p;
			}
		}
	}
	
	if (closestPigDistance == 99999) {
		_shark.setState(shark::WANDER_STATE);
		return;
	}

	path = _aStar.FindShortestPath(_shark.node(), *(closestPig->getClosestNode()));

	_shark.node(*(path.at(0)));

}

double huntState::calculateDistance(kmint::pigisland::pig* pig) {
	double distance = sqrt(pow(_shark.node().location().x() - pig->location().x(), 2) + pow(_shark.node().location().y() - pig->location().y(), 2));
	return distance;
}
}}