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
			auto others = pig.getNeighbours();
			auto wander = CalculateWanderForces(pig)*dna[pig::Forces::WANDER];
			auto cohesion = CalculateCohesionForces(pig,others)*dna[pig::Forces::COHESION];
			auto separation = CalculateSeparationForces(pig, others)*dna[pig::Forces::SEPARATION];
			auto alignment = CalculateAlignmentForces(pig,others)*dna[pig::Forces::ALIGNMENT];
			auto aToBoat = CalculateAttractionToBoat(pig)*dna[pig::Forces::ATTRACTIONTOBOAT];
			auto aToShark = CalculateAttractionToShark(pig)*dna[pig::Forces::ATTRACTIONTOSHARK];
			auto totalForce = wander + cohesion + separation + alignment + aToBoat + aToShark;
			return totalForce;
		}
		
		math::vector2d SteeringBehaviors::CalculateSeparationForces(const pig &pig,const std::vector<const pigisland::pig*>& neighbours) const
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


		math::vector2d SteeringBehaviors::CalculateAlignmentForces(const pig &pig,const std::vector<const pigisland::pig*>& neighbours) const
		{
			auto avgHeading = math::vector2d(0, 0);//pig.location();
			//const auto& neigbours = pig.getNeighbours();
			if (neighbours.size() > 0) {
				for (const auto& neighbour : neighbours) {
					avgHeading += neighbour->getHeading();
				}
				avgHeading /= neighbours.size();
				avgHeading -= pig.getHeading();
			}
			return avgHeading;
		}

		math::vector2d SteeringBehaviors::CalculateCohesionForces(const pig &pig,const std::vector<const pigisland::pig*>& neighbours) const
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

	}
}
