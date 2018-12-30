#include "..\..\..\include\kmint\pigisland\ActorContainer.hpp"
#include "../../../../libkmint/kmint_handout/libkmint/include/kmint/random.hpp"
#include "kmint/pigisland/island.hpp"
#include "kmint/pigisland/wall.hpp"
#include <algorithm>


namespace kmint {
namespace pigisland {

ActorContainer::ActorContainer(kmint::map::map_graph &g, play::stage& s):
	_g(g), _s(s)
{
	myShark = &(_s.build_actor<pigisland::shark>(_g, *this));
	myBoat = &(_s.build_actor<pigisland::boat>(_g));

	//borders
	s.build_actor<pigisland::wall>(math::vector2d{ 500.0f, 750.0f }, pigisland::wall::Face::NORTH);
	s.build_actor<pigisland::wall>(math::vector2d{ 500.0f, 10.0f }, pigisland::wall::Face::SOUTH);
	s.build_actor<pigisland::wall>(math::vector2d{ .0f, 325.0f }, pigisland::wall::Face::EAST);
	s.build_actor<pigisland::wall>(math::vector2d{ 1020.0f, 325.0f }, pigisland::wall::Face::WEST);
	
	//right top island
	islands.push_back(&(s.build_actor<pigisland::island>(math::vector2d{ 1020.0f, 0.0f }, 80)));
	islands.push_back(&(s.build_actor<pigisland::island>(math::vector2d{ 990.0f, 0.0f }, 80)));
	islands.push_back(&(s.build_actor<pigisland::island>(math::vector2d{ 1020.0f, 100.0f }, 30)));
	islands.push_back(&(s.build_actor<pigisland::island>(math::vector2d{ 1020.0f, 50.0f }, 30)));
	
	//bottom right island
	islands.push_back(&(s.build_actor<pigisland::island>(math::vector2d{ 925.0f, 750.0f }, 125)));
	islands.push_back(&(s.build_actor<pigisland::island>(math::vector2d{ 1020.0f, 625.0f }, 50)));
	islands.push_back(&(s.build_actor<pigisland::island>(math::vector2d{ 915.0f, 625.0f }, 30)));
	islands.push_back(&(s.build_actor<pigisland::island>(math::vector2d{ 915.0f, 575.0f }, 30)));
	islands.push_back(&(s.build_actor<pigisland::island>(math::vector2d{ 1020.0f, 750.0f }, 150)));
	
	//bottom left island
	islands.push_back(&(s.build_actor<pigisland::island>(math::vector2d{ 125.0f, 625.0f }, 75)));
	islands.push_back(&(s.build_actor<pigisland::island>(math::vector2d{ 175.0f, 575.0f }, 25)));
	
	//top left island
	islands.push_back(&(s.build_actor<pigisland::island>(math::vector2d{ 0.0f, 0.0f }, 100)));
	islands.push_back(&(s.build_actor<pigisland::island>(math::vector2d{ 100.0f, 0.0f }, 100)));
	islands.push_back(&(s.build_actor<pigisland::island>(math::vector2d{ 175.0f, 45.0f }, 27)));
	islands.push_back(&(s.build_actor<pigisland::island>(math::vector2d{ 225.0f, 45.0f }, 27)));
	islands.push_back(&(s.build_actor<pigisland::island>(math::vector2d{ 275.0f, 45.0f }, 27)));
	
	//statue
	islands.push_back(&(s.build_actor<pigisland::island>(math::vector2d{ 0.0f, 680.0f }, 50)));
	islands.push_back(&(s.build_actor<pigisland::island>(math::vector2d{ 50.0f, 680.0f }, 50)));

	for (int i = 0; i < 100; ++i) {
		auto location = random_scalar(0, islands.size());
		pigVector.push_back(&(_s.build_actor<pigisland::pig>(islands[location]->location(), 1, 1, 1, .05, 1, -1, _g, *myShark, *myBoat)));
	}
	startTime = now();
}

void ActorContainer::spawnPigs()
{
	int newPigsToSpawn = 1;//spawnOldPigs();
	spawnNewPigs(newPigsToSpawn);
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
		if (pigs->alive())
			continue;
		else {
			pigs->revive();
			spawnLeft -= 1;
		}
	}

	return spawnLeft;
}

bool ActorContainer::sortHelper(pig* pig1,pig* pig2)
{
	return pig1->timeAlive() > pig2->timeAlive();
}



void ActorContainer::spawnNewPigs(int const pigsToSpawn)
{	
	auto endTime = now() - startTime;
	for(auto& p:pigVector)
	{
		//4 walls
		//p->revive();
		int countCol = 0;
		auto x = random_scalar(100, 924);
		auto y = random_scalar(50, 728);
		p->setLocation(math::vector2d(x, y));
		for(auto island:islands)
		{
			if(collision(*p,*island))
			{
				countCol++;
			}
		}

		//_s.act(delta_time(0));
		while (countCol>0) {
			countCol = 0;
			x = random_scalar(100, 924);
			y = random_scalar(50, 728);
			p->setLocation(math::vector2d(x, y));
			//_s.act(delta_time(0));
			for (auto island : islands)
			{
				if (collision(*p, *island))
				{
					countCol++;
				}
			}
		}
	}

	//float totalFitnes = 0;
	//for(auto p:pigVector)
	//{
		//totalFitnes += to_seconds(p->timeAlive());
		//p->revive();
	//}

	std::sort(pigVector.begin(), pigVector.end(), [](pig* pig1, pig* pig2) {return pig1->timeAlive() > pig2->timeAlive();});
	for (auto p : pigVector)
	{
		//totalFitnes += to_seconds(p->timeAlive());
		p->revive();
	}

	startTime = now();
	
}

std::vector<pig*> ActorContainer::getAllAlive() const
{
	std::vector<pig*> returnVector;
	for each (auto pigs in pigVector)
	{
		if (pigs->alive()) {
			returnVector.push_back(pigs);
		}
	}
	return returnVector;
}

void ActorContainer::newRound() {
	spawnPigs();
}

}
}
