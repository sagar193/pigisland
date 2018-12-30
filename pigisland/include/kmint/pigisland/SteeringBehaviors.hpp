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
			math::vector2d CalculateWander(pig &pig) const;

			math::vector2d CalculateSeparation(const pig &pig,const std::vector<const play::actor*>& neighbours) const ;
			math::vector2d CalculateAlignment(const pig &pig,const std::vector<const play::actor*>& neighbours) const ;
			math::vector2d CalculateCohesion(const pig &pig, const std::vector<const play::actor*>& neighbours) const ;
			math::vector2d CalculateIslandAvoidance(const pig &pig, const std::vector<const play::actor*>& islands) const;
			
			math::vector2d CalculateAttractionToShark(pig &pig) const;
			math::vector2d CalculateAttractionToBoat(pig &pig) const;
		};
	}
}

#endif /* KMINT_PIGISLAND_SteeringBehaviors_HPP */