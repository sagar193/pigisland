#include "kmint/pigisland/SteeringBehaviors.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/boat.hpp"
#include <random>
#include <cmath>
#include "../../../../libkmint/kmint_handout/libkmint/include/kmint/play/actor.hpp"
#include "kmint/pigisland/island.hpp"
#include <iostream>


namespace kmint {
	namespace pigisland {
		SteeringBehaviors::SteeringBehaviors(){
		}

		kmint::math::vector2d SteeringBehaviors::CalculateForces(const pig &pig) const
		{
			auto dna = pig.getDNA();
			
			std::vector<const play::actor*> others;
			std::vector<const play::actor*> islands;
			
			auto totalForce = math::vector2d(0, 0);
			
			for(auto i = pig.begin_perceived();i!=pig.end_perceived();++i)
			{
				const play::actor *ptr = &(*i);
				if(dynamic_cast<const pigisland::pig*>(ptr))
				{
					others.push_back(ptr);
				}
				else if(dynamic_cast<const island*>(ptr))
				{
					islands.push_back(ptr);
				}
				else if(dynamic_cast<const boat*>(ptr))
				{
					totalForce+=CalculateSeek(pig, ptr->location())*dna[pig::Forces::ATTRACTIONTOBOAT];
				}
				else if (dynamic_cast<const shark*>(ptr))
				{
					totalForce += CalculateSeek(pig, ptr->location())*dna[pig::Forces::ATTRACTIONTOSHARK];
				}
			}

			totalForce += CalculateWander(pig);
			totalForce += CalculateCohesion(pig,others)*dna[pig::Forces::COHESION];
			totalForce += CalculateSeparation(pig, others)*dna[pig::Forces::SEPARATION];
			totalForce += CalculateAlignment(pig,others)*dna[pig::Forces::ALIGNMENT];
			return totalForce;
		}

		math::vector2d SteeringBehaviors::CalculateSeek(const pig &pig, const math::vector2d target) const
		{
			auto k = target - pig.location();
			if (k.x()*k.x() + k.y()*k.y()>0) {
				k = normalize(k);
				k *= pig.getMaxSpeed();
				k -= pig.getVelocity();
			}
;			return k;
		}

		math::vector2d SteeringBehaviors::CalculateSeparation(const pig &pig,const std::vector<const play::actor*>& neighbours) const
		{
			auto seperationVector = math::vector2d(0, 0);
			//auto neigbours = pig.getNeighbours();
				
			for (const auto& neighbour : neighbours) {
				auto toVector = pig.location() - neighbour->location();
				const auto& toVectorLength = toVector.x() * toVector.x() + toVector.y() * toVector.y();
				if (toVectorLength > 0) {
					toVector /= toVectorLength;
				}
				seperationVector += toVector;
			}
			return seperationVector;

		}

		math::vector2d SteeringBehaviors::CalculateWander(const pig &pig) const {
			const auto randX = (((double)rand() / (RAND_MAX))) * 2 - 1;
			const auto randY = (((double)rand() / (RAND_MAX))) * 2 - 1;
			
			auto wanderVector = math::vector2d(randX, randY);
			const auto wanderLength = wanderVector.x()*wanderVector.x() + wanderVector.y()*wanderVector.y();
			if (wanderLength > pig.getWanderJitter()) {
				wanderVector /= std::sqrt(wanderLength);
				wanderVector *= pig.getWanderRadius();
			}
			const auto& distance = (pig.heading()*pig.getWanderDistance());

			auto wander = wanderVector + distance;
			//const auto& totalWanderLength = wander.x()*wander.x() + wander.y()*wander.y();
			//if (totalWanderLength > 0) {
			//	wander /= std::sqrt(totalWanderLength);
			//}
			return wander;
		}


		math::vector2d SteeringBehaviors::CalculateAlignment(const pig &pig,const std::vector<const play::actor*>& neighbours) const
		{
			auto avgHeading = math::vector2d(0, 0);//pig.location();
			//const auto& neigbours = pig.getNeighbours();
			if (neighbours.size() > 0) {
				for (const auto& neighbour : neighbours) {
					
					avgHeading += neighbour->heading();
				}
				avgHeading /= neighbours.size();
				avgHeading -= pig.heading();
			}
			return avgHeading;
		}

		math::vector2d SteeringBehaviors::CalculateCohesion(const pig &pig,const std::vector<const play::actor*>& neighbours) const
		{
			auto cohessionVector = math::vector2d(0, 0);
			
			if (neighbours.size() > 0) {
				auto midpoint = math::vector2d(0, 0);
				for (const auto& neighbour : neighbours) {
					midpoint += neighbour->location();
				}
				midpoint /= neighbours.size();
				cohessionVector = CalculateSeek(pig,midpoint);
				//std::cout << cohessionVector.x() << " " << cohessionVector.y()<<"\n";
			}
			return cohessionVector;
		}

		

		math::vector2d SteeringBehaviors::CalculateIslandAvoidance(const pig &pig, const std::vector<const play::actor*>& islands) const
		{
			return CalculateCohesion(pig, islands) * -1;
		}


	}
}
