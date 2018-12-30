#pragma once
#include <vector>
#include "pig.hpp"
#include "shark.hpp"
#include "boat.hpp"
#include "island.hpp"

namespace kmint {
namespace pigisland {
class ActorContainer
{
public:
	ActorContainer(kmint::map::map_graph &g, play::stage& s);
	ActorContainer(const ActorContainer& other) = delete;
	ActorContainer(ActorContainer&& other) = delete;
	ActorContainer operator=(const ActorContainer& other) = delete;
	ActorContainer operator=(ActorContainer&& other) = delete;

	void addPigReference(pig* newPig);
	void newRound();
private:
	std::vector<pig*> pigVector;
	std::vector<island*> islands;
	time startTime;
	kmint::map::map_graph &_g;
	play::stage& _s;
	shark* myShark;
	boat* myBoat;
	void spawnPigs();

	int const spawnOldPigs();
	void spawnNewPigs(int const pigsToSpawn);
	std::vector<pig*> getAllAlive() const;

};
}
}
