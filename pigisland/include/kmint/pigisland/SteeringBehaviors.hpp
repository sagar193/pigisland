#ifndef KMINT_PIGISLAND_SteeringBehaviors_HPP
#define KMINT_PIGISLAND_SteeringBehaviors_HPP

#include "kmint/play.hpp"
#include "kmint/pigisland/pig.hpp"

namespace kmint {
	namespace pigisland {
		class SteeringBehaviors {
		public:
			SteeringBehaviors();
			math::vector2d CalculateForces(pig &pig) const;
			math::vector2d CalculateWanderForces(pig &pig) const;

			math::vector2d CalculateSeparationForces(const pig &pig,const std::vector<const pigisland::pig*>& neighbours) const ;
			math::vector2d CalculateAlignmentForces(const pig &pig,const std::vector<const pigisland::pig*>& neighbours) const ;
			math::vector2d CalculateCohesionForces(const pig &pig,const std::vector<const pigisland::pig*>& neighbours) const ;
			
			math::vector2d CalculateAttractionToShark(pig &pig) const;
			math::vector2d CalculateAttractionToBoat(pig &pig) const;
		};
	}
}

#endif /* KMINT_PIGISLAND_SteeringBehaviors_HPP */