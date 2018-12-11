#include "kmint/pigisland/SteeringBehaviors.hpp"

namespace kmint {
	namespace pigisland {
		SteeringBehaviors::SteeringBehaviors(kmint::pigisland::pig& pig) : pig(pig) {
		}

		kmint::math::vector2d SteeringBehaviors::CalculateForces()
		{
			return kmint::math::vector2d(.00000001f, .00000001f);
		}

		kmint::math::vector2d SteeringBehaviors::CalculateSeperationForces()
		{
			for (auto i = pig.begin_perceived(); i != pig.end_perceived(); ++i) {
				kmint::play::actor *ptr = &(*i);
				if (auto p = dynamic_cast<kmint::pigisland::pig*>(ptr); p) {
					std::cout << "saw something at " << p->location().x() << ", "
						<< p->location().y() << "\n";
				}
			}
		}
		kmint::math::vector2d SteeringBehaviors::CalculateAlignmentForces()
		{
			return kmint::math::vector2d(.00000001f, .00000001f);
		}
		kmint::math::vector2d SteeringBehaviors::CalculateCohesionForces()
		{
			return kmint::math::vector2d(.00000001f, .00000001f);
		}
	}
}
