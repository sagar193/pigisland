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
			enum Face
			{
				NORTH,
				SOUTH,
				WEST,
				EAST
			};
			explicit wall(math::vector2d location,Face face) : free_roaming_actor{ location }, drawable_{ *this, shark_image() }
			{
				this->face = face;
			}

			const ui::drawable &drawable() const override { return drawable_; }
			bool perceivable() const override { return true; }
			bool must_draw() const override { return false; }
			scalar radius() const override { return 10000.0f; }
			bool incorporeal() const override { return false; }
			double getLength() const { return 10; }
			Face getFace() const { return face; }

		private:
			play::image_drawable drawable_;
			Face face;
		};

	} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_WALL_HPP */
