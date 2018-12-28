#include "..\..\..\include\kmint\pigisland\ActorContainer.hpp"


namespace kmint {
namespace pigisland {

ActorContainer::ActorContainer(kmint::map::map_graph &g, play::stage& s):
	_g(g), _s(s)
{
	myShark = &(s.build_actor<pigisland::shark>(_g));
	myBoat = &(s.build_actor<pigisland::boat>(_g));
	for (int i = 0; i < 100; ++i) {
		pigVector.push_back(&(s.build_actor<pigisland::pig>(math::vector2d(i * 10.0f, i * 6.0f), 1, 1, 1, .05, -1, 1, _g, *myShark, *myBoat)));
	}
}

void ActorContainer::spawnPigs()
{
	int newPigsToSpawn = spawnOldPigs();
	///spawnNewPigs(newPigsToSpawn)
}

void ActorContainer::addPigReference(pig* newPig)
{
	pigVector.push_back(newPig);
}

int const ActorContainer::spawnOldPigs()
{
	int spawnLeft = 100;
	for each (auto pigs in pigVector)
	{
		///if pig is alive next
		///if pig is dead respawn, spawnLeft -1
	}

	return spawnLeft;
}

void ActorContainer::spawnNewPigs(int const pigsToSpawn)
{
	
}

}
}