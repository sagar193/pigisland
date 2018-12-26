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
			auto& totalForce = wander + cohession + seperation;
			return totalForce;
		}
		
		kmint::math::vector2d SteeringBehaviors::CalculateSeperationForces(kmint::pigisland::pig &pig) const
		{

			auto & midpoint = kmint::math::vector2d(0, 0);
			auto& neigbours = pig.getNeighbours();
			if (neigbours.size() > 0) {
				for (const auto& location : neigbours) {
					midpoint += location;
				}
				midpoint /= neigbours.size();
			}

			auto& midpointDistance = pig.location() - midpoint;
			return midpointDistance * pig.getSeperationForce();




			/*
			for (auto i = pig.begin_perceived(); i != pig.end_perceived(); ++i) {
				kmint::play::actor *ptr = &(*i);
				if (auto p = dynamic_cast<kmint::pigisland::pig*>(ptr); p) {
					//std::cout << "saw something at " << p->location().x() << ", "
					//	<< p->location().y() << "\n";
				}
			}
			return math::vector2d(0,0);*/
		}
		/*
		kmint::math::vector2d SteeringBehaviors::CalculateSeekForces(const play::free_roaming_actor& target) {
			auto force = math::vector2d(target.location().x() - pig.location().x(), target.location().y() - pig.location().y());
			return force * pig.getMaxSpeed();
		}*/

		kmint::math::vector2d SteeringBehaviors::CalculateWanderForces(kmint::pigisland::pig &pig) const {
			auto randX = (((double)rand() / (RAND_MAX))) * 2 - 1;
			auto randY = (((double)rand() / (RAND_MAX))) * 2 - 1;
			
			auto wanderVector = math::vector2d(randX, randY);
			auto wanderLength = wanderVector.x()*wanderVector.x() + wanderVector.y()*wanderVector.y();
			if (wanderLength > pig.getWanderJitter()) {
				wanderVector /= std::sqrt(wanderLength);
				wanderVector *= pig.getWanderRadius();
			}
			auto& distance = (pig.getHeading()*pig.getWanderDistance());
			return wanderVector+distance;
		}


		kmint::math::vector2d SteeringBehaviors::CalculateAlignmentForces(kmint::pigisland::pig &pig) const
		{
			return kmint::math::vector2d(.00000001f, .00000001f);
		}

		kmint::math::vector2d SteeringBehaviors::CalculateCohesionForces(kmint::pigisland::pig &pig) const 
		{
			auto & midpoint = kmint::math::vector2d(0,0);
			auto& neigbours = pig.getNeighbours();
			if (neigbours.size() > 0) {
				for (const auto& location : neigbours) {
					midpoint += location;
				}
				//midpoint /= neigbours.size();
			}

			auto& midpointDistance = midpoint - pig.location();
			return midpointDistance*pig.getCohessionForce();
		}

	}
}
