#include "kmint/pigisland/pig.hpp"
#include "kmint/math/angle.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include <cmath>

#include "kmint/pigisland/SteeringBehaviors.hpp"

namespace kmint {
namespace pigisland {

namespace {

math::vector2d random_vector() {
  auto x = random_scalar(100, 924);
  auto y = random_scalar(50, 728);
  return {x, y};
}
} // namespace

pig::pig(math::vector2d location)
	: free_roaming_actor{ random_vector()/*location*/ }, drawable_{ *this, pig_image() }, steeringBehavior{ SteeringBehaviors() } {}
      

void pig::act(delta_time dt) {
  free_roaming_actor::act(dt);
  math::vector2d steeringForce = steeringBehavior.CalculateForces();
  auto acceleration = steeringForce / mass;
  dt.count();
  velocity += acceleration * dt.count();
  auto velocityLength = std::sqrt(velocity.x() * velocity.x() + (velocity.y() * velocity.y()));
  if (velocityLength > 0 && velocityLength > maxSpeed) {
	  velocity /= velocityLength *= maxSpeed;
  }
  move(velocity);
}
} // namespace pigisland

} // namespace kmint
