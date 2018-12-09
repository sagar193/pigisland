#ifndef KMINT_PIGISLAND_SteeringBehaviors_HPP
#define KMINT_PIGISLAND_SteeringBehaviors_HPP

#include "kmint/play.hpp"

namespace kmint {
	namespace pigisland {
		class SteeringBehaviors {
		public:
			kmint::math::vector2d CalculateForces();
		};
	}
}

#endif /* KMINT_PIGISLAND_SteeringBehaviors_HPP */