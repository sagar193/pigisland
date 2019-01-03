#ifndef KMINT_PIGISLAND_ISLAND_HPP
#define KMINT_PIGISLAND_ISLAND_HPP

#include "kmint/play.hpp"
#include "kmint/pigisland/pig.hpp"
#include <map>
#include "states/shark/huntState.hpp"

//class MovingActor;

namespace kmint {
	namespace pigisland {

		class island : public play::free_roaming_actor {
		public:
			
			explicit island(math::vector2d location,double radius) : free_roaming_actor{ location }, drawable_{ *this, boat_image() }
			{
				this->radius_ = radius;
			}

			const ui::drawable &drawable() const override { return drawable_; }
			bool perceivable() const override { return true; }
			bool must_draw() const override { return false; }
			scalar radius() const override { return radius_; }
			bool incorporeal() const override { return false; }


		private:
			play::image_drawable drawable_;
			scalar radius_;
		};

	} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_WALL_HPP */
