#include "kmint/pigisland/SteeringBehaviors.hpp"

namespace kmint {
	namespace pigisland {
		kmint::math::vector2d SteeringBehaviors::CalculateForces()
		{
			return kmint::math::vector2d(.00000001f, .00000001f);
		}
	}
}
