#include "kmint/pigisland/pig.hpp"
#include "kmint/math/angle.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include <cmath>

#include "kmint/pigisland/SteeringBehaviors.hpp"
#include <iostream>

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
	: free_roaming_actor{ random_vector()/*location*/ }, drawable_{ *this, pig_image() }/*, steeringBehavior{ kmint::pigisland::SteeringBehaviors(*this) }*/ {
}
      

void pig::act(delta_time dt) {
  free_roaming_actor::act(dt);
  math::vector2d steeringForce = steeringBehavior->CalculateForces(*this);
  auto acceleration = steeringForce / mass;
  dt.count();
  velocity += acceleration * dt.count();
  auto x = velocity.x();
  auto y = velocity.y();
  auto velocityLength = (x*x) + (y*y);
  if (velocityLength > 0 && velocityLength > maxSpeed*maxSpeed) {
	  velocity /= std::sqrt(velocityLength);
	  velocity *= maxSpeed;
  }

  std::cout << velocity<<std::endl;
  move(velocity);
  

}
} // namespace pigisland

} // namespace kmint
