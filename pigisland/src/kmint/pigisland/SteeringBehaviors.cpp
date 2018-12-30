#include "kmint/pigisland/SteeringBehaviors.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/boat.hpp"
#include <random>
#include <cmath>
#include "../../../../libkmint/kmint_handout/libkmint/include/kmint/play/actor.hpp"
#include "kmint/pigisland/island.hpp"


namespace kmint {
	namespace pigisland {
		SteeringBehaviors::SteeringBehaviors(){
		}

		kmint::math::vector2d SteeringBehaviors::CalculateForces(pig &pig) const
		{
			auto dna = pig.getDNA();
			//const auto others = pig.getNeighbours();
			std::vector<const play::actor*> others;
			std::vector<const play::actor*> islands;
			for(auto i = pig.begin_perceived();i!=pig.end_perceived();++i)
			{
				play::actor *ptr = &(*i);
				if(dynamic_cast<pigisland::pig*>(ptr))
				{
					others.push_back(ptr);
				}
				else if(dynamic_cast<island*>(ptr))
				{
					islands.push_back(ptr);
				}
			}

			const auto wander = CalculateWander(pig)*dna[pig::Forces::WANDER];
			const auto cohesion = CalculateCohesion(pig,others)*dna[pig::Forces::COHESION];
			const auto separation = CalculateSeparation(pig, others)*dna[pig::Forces::SEPARATION];
			const auto alignment = CalculateAlignment(pig,others)*dna[pig::Forces::ALIGNMENT];
			const auto aToBoat = CalculateAttractionToBoat(pig)*dna[pig::Forces::ATTRACTIONTOBOAT];
			const auto aToShark = CalculateAttractionToShark(pig)*dna[pig::Forces::ATTRACTIONTOSHARK];
			const auto totalForce = wander + cohesion + separation + alignment + aToBoat + aToShark; //+ islandAvoidance;
			return totalForce;
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

		math::vector2d SteeringBehaviors::CalculateWander(pig &pig) const {
			const auto randX = (((double)rand() / (RAND_MAX))) * 2 - 1;
			const auto randY = (((double)rand() / (RAND_MAX))) * 2 - 1;
			
			auto wanderVector = math::vector2d(randX, randY);
			const auto wanderLength = wanderVector.x()*wanderVector.x() + wanderVector.y()*wanderVector.y();
			if (wanderLength > pig.getWanderJitter()) {
				wanderVector /= std::sqrt(wanderLength);
				wanderVector *= pig.getWanderRadius();
			}
			const auto& distance = (pig.getHeading()*pig.getWanderDistance());

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
				avgHeading -= pig.getHeading();
			}
			return avgHeading;
		}

		math::vector2d SteeringBehaviors::CalculateCohesion(const pig &pig,const std::vector<const play::actor*>& neighbours) const
		{
			auto cohessionVector = math::vector2d(0, 0);
			
			//auto neigbours = pig.getNeighbours();
			if (neighbours.size() > 0) {
				auto midpoint = math::vector2d(0, 0);
				for (const auto& neighbour : neighbours) {
					midpoint += neighbour->location();
				}
				midpoint /= neighbours.size();
				cohessionVector = midpoint - pig.location();
				//const auto& cohessionLength = cohessionVector.x() *cohessionVector.x() + cohessionVector.y()*cohessionVector.y();
				//if (cohessionLength > 0) {
				//	cohessionVector = cohessionVector / std::sqrt(cohessionLength);
				//}
			}
			return cohessionVector;
		}

		math::vector2d SteeringBehaviors::CalculateAttractionToShark(pig &pig) const {
			auto attractionVector = pig.getShark()->location() - pig.location();
			//pig.getBoat() = nullptr;
			const auto& attractionLength = attractionVector.x() *attractionVector.x() + attractionVector.y()*attractionVector.y();
			if (attractionLength > 0 && attractionLength<=(pig.range_of_perception()*pig.range_of_perception())) {
				//attractionVector = attractionVector / std::sqrt(attractionLength);
				return attractionVector;
			}
			return math::vector2d(0, 0);
		}

		math::vector2d SteeringBehaviors::CalculateAttractionToBoat(pig &pig) const {
			auto attractionVector = pig.getBoat()->location() - pig.location();
			const auto& attractionLength = attractionVector.x() *attractionVector.x() + attractionVector.y()*attractionVector.y();
			if (attractionLength > 0 && attractionLength <= (pig.range_of_perception()*pig.range_of_perception())) {
				//attractionVector = attractionVector / std::sqrt(attractionLength);
				return attractionVector;
			}
			return math::vector2d(0, 0);
		}

		math::vector2d SteeringBehaviors::CalculateIslandAvoidance(const pig &pig, const std::vector<const play::actor*>& islands) const
		{
			return CalculateCohesion(pig, islands) * -1;
		}


	}
}
