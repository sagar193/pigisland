#ifndef KMINT_PIGISLAND_MovingActor_HPP
#define KMINT_PIGISLAND_MovingActor_HPP

#include "kmint/play.hpp"
#include "kmint/pigisland/SteeringBehaviors.hpp"

namespace kmint {
	namespace pigisland {
		class MovingActor : public play::free_roaming_actor {
		public:
			MovingActor() = default;
		protected:
			// normalized
			kmint::math::vector2d heading;
			kmint::math::vector2d side;
			double mass;
			double maxSpeed;
			double maxForce;
			double maxTurnRate;


		};
	}
}

#endif /* KMINT_PIGISLAND_MovingActor_HPP */