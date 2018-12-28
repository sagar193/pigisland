#include "kmint/pigisland/SteeringBehaviors.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/boat.hpp"
#include <random>
#include <cmath>



namespace kmint {
	namespace pigisland {
		SteeringBehaviors::SteeringBehaviors(){
		}

		kmint::math::vector2d SteeringBehaviors::CalculateForces(pig &pig) const
		{
			auto dna = pig.getDNA();
			auto wander = CalculateWanderForces(pig)*dna[pig::Forces::WANDER];
			auto cohession = CalculateCohesionForces(pig)*dna[pig::Forces::COHESSION];
			auto seperation = CalculateSeparationForces(pig)*dna[pig::Forces::SEPARATION];
			auto alignment = CalculateAlignmentForces(pig)*dna[pig::Forces::ALLIGNMENT];
			auto aToBoat = CalculateAttractionToBoat(pig)*dna[pig::Forces::ATTRACTIONTOBOAT];
			auto aToShark = CalculateAttractionToShark(pig)*dna[pig::Forces::ATTRACTIONTOSHARK];
			auto totalForce = wander + cohession + seperation + alignment + aToBoat + aToShark;
			return totalForce;
		}
		
		math::vector2d SteeringBehaviors::CalculateSeparationForces(pig &pig) const
		{
			auto seperationVector = math::vector2d(0, 0);
			auto neigbours = pig.getNeighbours();
				
			for (const auto& neighbour : neigbours) {
				auto toVector = pig.location() - neighbour->location();
				const auto& toVectorLength = toVector.x() * toVector.x() + toVector.y() * toVector.y();
				if (toVectorLength > 0) {
					toVector /= toVectorLength;
				}
				seperationVector += toVector;
			}
			return seperationVector;

		}

		math::vector2d SteeringBehaviors::CalculateWanderForces(pig &pig) const {
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


		math::vector2d SteeringBehaviors::CalculateAlignmentForces(pig &pig) const
		{
			auto avgHeading = math::vector2d(0, 0);//pig.location();
			const auto& neigbours = pig.getNeighbours();
			if (neigbours.size() > 0) {
				for (const auto& neighbour : neigbours) {
					avgHeading += neighbour->getHeading();
				}
				avgHeading /= neigbours.size();
				avgHeading -= pig.getHeading();
			}
			return avgHeading;
		}

		math::vector2d SteeringBehaviors::CalculateCohesionForces(pig &pig) const 
		{
			auto cohessionVector = math::vector2d(0, 0);
			
			auto neigbours = pig.getNeighbours();
			if (neigbours.size() > 0) {
				auto midpoint = math::vector2d(0, 0);
				for (const auto& neighbour : neigbours) {
					midpoint += neighbour->location();
				}
				midpoint /= neigbours.size();
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

	}
}
