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
  
  //Calculate forces
  const auto& steering_force = steeringBehavior->CalculateForces(*this);
  const auto& acceleration = steering_force / mass;

  //Add new acceleration to velocity
  velocity += acceleration * to_seconds(dt);

  //Set to max speed
  heading += velocity;
	
  const auto& velocity_length = (heading.x()*heading.x()) + (heading.y()*heading.y());
  if (velocity_length > 0 && velocity_length > maxSpeed*maxSpeed) {
	  heading /= std::sqrt(velocity_length);
	  heading *= maxSpeed;
  }

  //heading += velocity;

  move(heading);
  
}
} // namespace pigisland

} // namespace kmint
