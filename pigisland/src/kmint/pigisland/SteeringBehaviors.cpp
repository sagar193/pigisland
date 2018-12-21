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
			return CalculateWanderForces(pig);
		}
		
		kmint::math::vector2d SteeringBehaviors::CalculateSeperationForces(kmint::pigisland::pig &pig)
		{
			for (auto i = pig.begin_perceived(); i != pig.end_perceived(); ++i) {
				kmint::play::actor *ptr = &(*i);
				if (auto p = dynamic_cast<kmint::pigisland::pig*>(ptr); p) {
					//std::cout << "saw something at " << p->location().x() << ", "
					//	<< p->location().y() << "\n";
				}
			}
			return math::vector2d(0,0);
		}
		/*
		kmint::math::vector2d SteeringBehaviors::CalculateSeekForces(const play::free_roaming_actor& target) {
			auto force = math::vector2d(target.location().x() - pig.location().x(), target.location().y() - pig.location().y());
			return force * pig.getMaxSpeed();
		}*/

		kmint::math::vector2d SteeringBehaviors::CalculateWanderForces(kmint::pigisland::pig &pig) const {
			auto randX = (((double)rand() / (RAND_MAX))) * 2 - 1;
			auto randY = (((double)rand() / (RAND_MAX))) * 2 - 1;
			
			//auto j = pig.getWanderJitter();
			auto x = randX;//* j;
			auto y = randY; //* j;

			auto wanderVector = math::vector2d(x, y);
			auto wanderLength = wanderVector.x()*wanderVector.x() + wanderVector.y()*wanderVector.y();
			if (wanderLength > pig.getWanderJitter()) {
				wanderVector /= std::sqrt(wanderLength);
				wanderVector *= pig.getWanderRadius();
			}
			return wanderVector+(pig.getHeading()*pig.getWanderDistance());
		}
















		/*
		kmint::math::vector2d SteeringBehaviors::CalculateAlignmentForces()
		{
			return kmint::math::vector2d(.00000001f, .00000001f);
		}

		kmint::math::vector2d SteeringBehaviors::CalculateCohesionForces()
		{
			return kmint::math::vector2d(.00000001f, .00000001f);
		}*/
	}
}
