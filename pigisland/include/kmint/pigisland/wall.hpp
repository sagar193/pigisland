#ifndef KMINT_PIGISLAND_WALL_HPP
#define KMINT_PIGISLAND_WALL_HPP

#include "kmint/play.hpp"
#include "kmint/pigisland/pig.hpp"
#include <map>
#include "states/shark/huntState.hpp"

//class MovingActor;

namespace kmint {
	namespace pigisland {

		class wall : public play::free_roaming_actor {
		public:

			explicit wall(math::vector2d location) : free_roaming_actor{ location }, drawable_{ *this, shark_image() } {}

			const ui::drawable &drawable() const override { return drawable_; }
			bool perceivable() const override { return true; }
			bool must_draw() const override { return true; }
			scalar radius() const override { return 55.0f; }
			bool incorporeal() const override { return false; }

		private:
			play::image_drawable drawable_;
		};

	} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_WALL_HPP */
