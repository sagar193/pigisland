#include "..\..\..\include\kmint\pigisland\ActorContainer.hpp"
#include "../../../../libkmint/kmint_handout/libkmint/include/kmint/random.hpp"
#include "kmint/pigisland/island.hpp"
#include "kmint/pigisland/wall.hpp"
#include <algorithm>
#include <iostream>


namespace kmint {
namespace pigisland {

ActorContainer::ActorContainer(kmint::map::map_graph &g, play::stage& s/*,map::map& map*/):
	_g(g), _s(s)
{
	myShark = &(_s.build_actor<pigisland::shark>(_g, *this));
	myBoat = &(_s.build_actor<pigisland::boat>(_g));

	createInitWalls();
	createInitIslands();

	for (int i = 0; i < 100; ++i) {
		auto location = random_int(0, islands.size());
		
		pigVector.push_back(&(_s.build_actor<pigisland::pig>(islands[location]->location(), 
			random_scalar(0, 1), random_scalar(0, 1), random_scalar(0, 1), random_scalar(0, .005), random_scalar(-1, 1), random_scalar(-1, 1), _g, *myShark, *myBoat)));
	}
}

void ActorContainer::createInitWalls() 
{
	//borders
	int count = 10;
	//for()
	_s.build_actor<pigisland::wall>(math::vector2d{ 500.0f, 750.0f }, pigisland::wall::Face::NORTH);
	_s.build_actor<pigisland::wall>(math::vector2d{ 500.0f, 10.0f }, pigisland::wall::Face::SOUTH);
	_s.build_actor<pigisland::wall>(math::vector2d{ .0f, 325.0f }, pigisland::wall::Face::EAST);
	_s.build_actor<pigisland::wall>(math::vector2d{ 1020.0f, 325.0f }, pigisland::wall::Face::WEST);
}

void ActorContainer::createInitIslands()
{
	//right top island
	islands.push_back(&(_s.build_actor<pigisland::island>(math::vector2d{ 1020.0f, 0.0f }, 80)));
	islands.push_back(&(_s.build_actor<pigisland::island>(math::vector2d{ 990.0f, 0.0f }, 80)));
	islands.push_back(&(_s.build_actor<pigisland::island>(math::vector2d{ 1020.0f, 100.0f }, 30)));
	islands.push_back(&(_s.build_actor<pigisland::island>(math::vector2d{ 1020.0f, 50.0f }, 30)));

	//bottom right island
	islands.push_back(&(_s.build_actor<pigisland::island>(math::vector2d{ 925.0f, 750.0f }, 125)));
	islands.push_back(&(_s.build_actor<pigisland::island>(math::vector2d{ 1020.0f, 625.0f }, 50)));
	islands.push_back(&(_s.build_actor<pigisland::island>(math::vector2d{ 915.0f, 625.0f }, 30)));
	islands.push_back(&(_s.build_actor<pigisland::island>(math::vector2d{ 915.0f, 575.0f }, 30)));
	islands.push_back(&(_s.build_actor<pigisland::island>(math::vector2d{ 1020.0f, 750.0f }, 150)));

	//bottom left island
	islands.push_back(&(_s.build_actor<pigisland::island>(math::vector2d{ 125.0f, 625.0f }, 75)));
	islands.push_back(&(_s.build_actor<pigisland::island>(math::vector2d{ 175.0f, 575.0f }, 25)));

	//top left island
	islands.push_back(&(_s.build_actor<pigisland::island>(math::vector2d{ 0.0f, 0.0f }, 100)));
	islands.push_back(&(_s.build_actor<pigisland::island>(math::vector2d{ 100.0f, 0.0f }, 100)));
	islands.push_back(&(_s.build_actor<pigisland::island>(math::vector2d{ 175.0f, 45.0f }, 27)));
	islands.push_back(&(_s.build_actor<pigisland::island>(math::vector2d{ 225.0f, 45.0f }, 27)));
	islands.push_back(&(_s.build_actor<pigisland::island>(math::vector2d{ 275.0f, 45.0f }, 27)));

	//statue
	islands.push_back(&(_s.build_actor<pigisland::island>(math::vector2d{ 0.0f, 680.0f }, 50)));
	islands.push_back(&(_s.build_actor<pigisland::island>(math::vector2d{ 0.0f, 710.0f }, 50)));
	islands.push_back(&(_s.build_actor<pigisland::island>(math::vector2d{ 50.0f, 680.0f }, 50)));

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


bool ActorContainer::sortHelper(pig* pig1,pig* pig2)
{
	return pig1->timeAlive() > pig2->timeAlive();
}



void ActorContainer::spawnNewPigs(int const pigsToSpawn)
{	

	std::map<pig::Forces, double> avgdna;

	avgdna[pig::Forces::ATTRACTIONTOSHARK] = 0;
	avgdna[pig::Forces::ATTRACTIONTOBOAT] = 0;
	avgdna[pig::Forces::WANDER] = 0;
	avgdna[pig::Forces::COHESION] = 0;
	avgdna[pig::Forces::ALIGNMENT] = 0;
	avgdna[pig::Forces::SEPARATION] = 0;

	for(auto& p:pigVector)
	{
		avgdna[pig::Forces::ATTRACTIONTOSHARK] += p->getDNA()[pig::Forces::ATTRACTIONTOSHARK];
		avgdna[pig::Forces::ATTRACTIONTOBOAT] += p->getDNA()[pig::Forces::ATTRACTIONTOBOAT];
		avgdna[pig::Forces::WANDER] += p->getDNA()[pig::Forces::WANDER];
		avgdna[pig::Forces::COHESION] += p->getDNA()[pig::Forces::COHESION];
		avgdna[pig::Forces::ALIGNMENT] += p->getDNA()[pig::Forces::ALIGNMENT];
		avgdna[pig::Forces::SEPARATION] += p->getDNA()[pig::Forces::SEPARATION];


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


	std::vector<pig*> candidates;
	std::sort(pigVector.begin(), pigVector.end(), [](pig* pig1, pig* pig2) {return pig1->timeAlive() > pig2->timeAlive();});
	float totalFitness = 0;
	float maxFitness = 0;
	for (auto p : pigVector)
	{
		totalFitness += to_seconds(p->timeAlive());
		if (candidates.size() < countCandidates)
		{
			candidates.push_back(p);
			maxFitness += to_seconds(p->timeAlive());
			//cumulativeFitnis.push_back(to_seconds(p->timeAlive()) + last);
		}
	}

	std::cout << "avg fitness " << (totalFitness/pigVector.size())/to_seconds(myShark->getPlayTime())<< '\n';
	if(to_seconds(myShark->getPlayTime()) == 0)
	{
		int k = 0;
	}
	std::cout << "a to shark " << avgdna[pig::Forces::ATTRACTIONTOSHARK] / 100 << '\n';
	std::cout << "a to boat " << avgdna[pig::Forces::ATTRACTIONTOBOAT] / 100 << '\n';
	std::cout << "cohesion " << avgdna[pig::Forces::COHESION] / 100 << '\n';
	std::cout << "alignment " << avgdna[pig::Forces::ALIGNMENT] / 100 << '\n';
	std::cout << "separation " << avgdna[pig::Forces::SEPARATION] / 100 << '\n';
	std::cout << '\n';

	for (auto currentP : pigVector)
	{
		float last = to_seconds(candidates[candidates.size() - 1]->timeAlive());
		const auto papachance = random_scalar(to_seconds(candidates[candidates.size()-1]->timeAlive()), maxFitness);
		pig* papa = nullptr;
		const auto mamachance = random_scalar(to_seconds(candidates[candidates.size()-1]->timeAlive()), maxFitness);
		pig* mama = nullptr;
		for (auto p : candidates) {
			if(papachance >=last && papachance <=(to_seconds(p->timeAlive())+last))
			{
				papa = p;
			}
			if (mamachance >= last && mamachance <= (to_seconds(p->timeAlive()) + last))
			{
				mama = p;
			}
			last += to_seconds(p->timeAlive());
		}
		if(mama == nullptr || papa ==nullptr)
		{
			int  k = 0;
		}
		
		currentP->spliceDNA(*papa, *mama);

	}

	for (auto currentP : pigVector)
	{
		currentP->revive();
	}

	
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
