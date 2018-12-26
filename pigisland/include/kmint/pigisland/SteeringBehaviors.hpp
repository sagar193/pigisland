#ifndef KMINT_PIGISLAND_SteeringBehaviors_HPP
#define KMINT_PIGISLAND_SteeringBehaviors_HPP

#include "kmint/play.hpp"
#include "kmint/pigisland/pig.hpp"

namespace kmint {
	namespace pigisland {
		class SteeringBehaviors {
		public:
			SteeringBehaviors();
			void getNeighbours();
			kmint::math::vector2d CalculateForces(kmint::pigisland::pig &pig) const;
			
			kmint::math::vector2d CalculateWanderForces(kmint::pigisland::pig &pig) const;
			
			kmint::math::vector2d CalculateSeekForces(const play::free_roaming_actor& target);

			kmint::math::vector2d CalculateSeperationForces(kmint::pigisland::pig &pig) const ;
			kmint::math::vector2d CalculateAlignmentForces(kmint::pigisland::pig &pig) const ;
			kmint::math::vector2d CalculateCohesionForces(kmint::pigisland::pig &pig) const ;
			
		private:

			
			

			//std::vector<kmint::pigisland::pig> neighbours;
		};
	}
}

#endif /* KMINT_PIGISLAND_SteeringBehaviors_HPP */