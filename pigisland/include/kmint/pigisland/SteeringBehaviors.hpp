#ifndef KMINT_PIGISLAND_SteeringBehaviors_HPP
#define KMINT_PIGISLAND_SteeringBehaviors_HPP

#include "kmint/play.hpp"
#include "kmint/pigisland/pig.hpp"

namespace kmint {
	namespace pigisland {
		class SteeringBehaviors {
		public:
			SteeringBehaviors(kmint::pigisland::pig &pig);
			void getNeighbours();
			kmint::math::vector2d CalculateForces();
			kmint::math::vector2d CalculateSeperationForces();
			kmint::math::vector2d CalculateAlignmentForces();
			kmint::math::vector2d CalculateCohesionForces();
		private:
			kmint::pigisland::pig &pig;
			std::vector<kmint::pigisland::pig> neighbours;
		};
	}
}

#endif /* KMINT_PIGISLAND_SteeringBehaviors_HPP */