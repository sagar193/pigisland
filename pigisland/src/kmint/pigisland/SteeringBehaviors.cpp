#include "kmint/pigisland/SteeringBehaviors.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/boat.hpp"
#include <random>
#include <cmath>
#include "../../../../libkmint/kmint_handout/libkmint/include/kmint/play/actor.hpp"
#include "kmint/pigisland/island.hpp"
#include "../../../../libkmint/kmint_handout/libkmint/include/kmint/random.hpp"


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
				if(const auto p = dynamic_cast<const pigisland::pig*>(ptr);p)
				{
					if (dot(pig.heading(), ptr->location() - pig.location()) > 0) {
						others.push_back(ptr);
					}
				}
				else if(dynamic_cast<const island*>(ptr))
				{
					islands.push_back(ptr);
				}
				else if(dynamic_cast<const boat*>(ptr))
				{
					totalForce += dna[pig::Forces::ATTRACTIONTOBOAT] * CalculateSeek(pig,ptr->location());
				}
				else if(dynamic_cast<const shark*>(ptr))
				{
					totalForce += dna[pig::Forces::ATTRACTIONTOSHARK] * CalculateSeek(pig, ptr->location());
				}
			}

			totalForce += CalculateWander(pig);
			totalForce += CalculateCohesion(pig,others)*dna[pig::Forces::COHESION];
			totalForce += CalculateSeparation(pig, others)*dna[pig::Forces::SEPARATION];
			totalForce += CalculateAlignment(pig,others)*dna[pig::Forces::ALIGNMENT];
			totalForce += CalculateIslandAvoidance(pig,islands);
			return totalForce;
		}
		
		math::vector2d SteeringBehaviors::CalculateSeparation(const pig &pig,const std::vector<const play::actor*>& neighbours) const
		{
			auto separationVector = math::vector2d(0, 0);
				
			for (const auto& neighbour : neighbours) {
				auto toVector = pig.location() - neighbour->location();
				const auto& toVectorLength = toVector.x() * toVector.x() + toVector.y() * toVector.y();
				if (toVectorLength > 0) {
					toVector /= toVectorLength;
				}
				separationVector += toVector;
			}
			return separationVector;

		}

		math::vector2d SteeringBehaviors::CalculateWander(const pig &pig) const {
			const auto randX = random_scalar(-1, 1);
			const auto randY = random_scalar(-1, 1);
			
			auto wanderVector = math::vector2d(randX, randY);
			const auto wanderLength = wanderVector.x()*wanderVector.x() + wanderVector.y()*wanderVector.y();
			if (wanderLength > pig.getWanderJitter()) {
				wanderVector /= std::sqrt(wanderLength);
				wanderVector *= pig.getWanderRadius();
			}
			const auto& distance = (pig.heading()*pig.getWanderDistance());

			const auto wander = wanderVector + distance;
			return wander;
		}

		math::vector2d SteeringBehaviors::CalculateSeek(const pig& pig, math::vector2d target) const
		{
			return ((normalize(target - pig.location()))*pig.getMaxSpeed())-pig.getVelocity();
		}



		math::vector2d SteeringBehaviors::CalculateAlignment(const pig &pig,const std::vector<const play::actor*>& neighbours) const
		{
			auto avgHeading = math::vector2d(0, 0);
			if (!neighbours.empty()) {
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
			auto cohesionVector = math::vector2d(0, 0);
			
			if (!neighbours.empty()) {
				auto midpoint = math::vector2d(0, 0);
				for (const auto& neighbour : neighbours) {
					midpoint += neighbour->location();
				}
				midpoint /= neighbours.size();
				cohesionVector = CalculateSeek(pig,midpoint);
			}
			return cohesionVector;
		}


		math::vector2d SteeringBehaviors::CalculateIslandAvoidance(const pig &pig, const std::vector<const play::actor*>& islands) const
		{
			return CalculateCohesion(pig, islands) * -1;
		}


	}
}
