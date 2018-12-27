#include "kmint/pigisland/SteeringBehaviors.hpp"
#include <random>
#include <cmath>

namespace kmint {
	namespace pigisland {
		SteeringBehaviors::SteeringBehaviors(){
		}

		kmint::math::vector2d SteeringBehaviors::CalculateForces(kmint::pigisland::pig &pig) const
		{
			//return kmint::math::vector2d(.00000001f, .00000001f);
			auto& wander = CalculateWanderForces(pig);
			auto& cohession = CalculateCohesionForces(pig);
			auto& seperation = CalculateSeperationForces(pig);
			auto& alignment = CalculateAlignmentForces(pig);
			auto& totalForce = wander + cohession + seperation + alignment;
			return totalForce;
		}
		
		kmint::math::vector2d SteeringBehaviors::CalculateSeperationForces(kmint::pigisland::pig &pig) const
		{
			auto & seperationVector = kmint::math::vector2d(0, 0);
			auto& neigbours = pig.getNeighbours(pig.getSeperationDistance());
				
			for (const auto& neighbour : neigbours) {
				auto& toVector = pig.location() - neighbour->location();
				const auto& toVectorLength = toVector.x() * toVector.x() + toVector.y() * toVector.y();
				if (toVectorLength > 0) {
					toVector /= toVectorLength;
				}
				seperationVector += toVector;
			}
			return seperationVector * pig.getSeperationForce();

		}

		kmint::math::vector2d SteeringBehaviors::CalculateWanderForces(kmint::pigisland::pig &pig) const {
			const auto randX = (((double)rand() / (RAND_MAX))) * 2 - 1;
			const auto randY = (((double)rand() / (RAND_MAX))) * 2 - 1;
			
			auto wanderVector = math::vector2d(randX, randY);
			const auto wanderLength = wanderVector.x()*wanderVector.x() + wanderVector.y()*wanderVector.y();
			if (wanderLength > pig.getWanderJitter()) {
				wanderVector /= std::sqrt(wanderLength);
				wanderVector *= pig.getWanderRadius();
			}
			const auto& distance = (pig.getHeading()*pig.getWanderDistance());

			auto& wander = wanderVector + distance;
			const auto& totalWanderLength = wander.x()*wander.x() + wander.y()*wander.y();
			if (totalWanderLength > 0) {
				wander /= std::sqrt(totalWanderLength);
			}
			return wander * pig.getWanderForce();
		}


		kmint::math::vector2d SteeringBehaviors::CalculateAlignmentForces(kmint::pigisland::pig &pig) const
		{
			auto & avgHeading = kmint::math::vector2d(0, 0);//pig.location();
			const auto& neigbours = pig.getNeighbours(pig.range_of_perception());
			if (neigbours.size() > 0) {
				for (const auto& neighbour : neigbours) {
					avgHeading += neighbour->getHeading();
				}
				avgHeading /= neigbours.size();
				avgHeading -= pig.getHeading();
			}
			return avgHeading * pig.getAlignmentForce();
		}

		kmint::math::vector2d SteeringBehaviors::CalculateCohesionForces(kmint::pigisland::pig &pig) const 
		{
			auto& cohessionVector = kmint::math::vector2d(0, 0);
			
			auto& neigbours = pig.getNeighbours(pig.range_of_perception());
			if (neigbours.size() > 0) {
				auto & midpoint = kmint::math::vector2d(0, 0);
				for (const auto& neighbour : neigbours) {
					midpoint += neighbour->location();
				}
				midpoint /= neigbours.size();
				cohessionVector = midpoint - pig.location();
				const auto& cohessionLength = cohessionVector.x() *cohessionVector.x() + cohessionVector.y()*cohessionVector.y();
				if (cohessionLength > 0) {
					cohessionVector = cohessionVector / std::sqrt(cohessionLength);
				}
			}
			return cohessionVector*pig.getCohessionForce();
		}

	}
}
