#include "kmint/pigisland/pig.hpp"
#include "kmint/math/angle.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include <cmath>

#include "kmint/pigisland/SteeringBehaviors.hpp"
#include <iostream>
#include <vector>

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

  const auto& velocity_length = (velocity.x()*velocity.x()) + (velocity.y()*velocity.y());
  if (velocity_length > 0) {
	  const auto newHeading = velocity/ std::sqrt(velocity_length);
	  heading = newHeading;
	  if (velocity_length > maxSpeed*maxSpeed) {
		  velocity = newHeading * maxSpeed;
	  }
  }
  std::cout << velocity.x() << "    " << velocity.y() << std::endl;
  
  
  move(velocity);
}

std::vector<kmint::math::vector2d> pig::getNeighbours() {
	std::vector<kmint::math::vector2d> neighbours;
	for (auto i = begin_perceived(); i != end_perceived(); ++i) {
		kmint::play::actor *ptr = &(*i);
		if (auto p = dynamic_cast<kmint::pigisland::pig*>(ptr); p) {
			//std::cout << "saw something at " << p->location().x() << ", "
			//	<< p->location().y() << "\n";
			auto& distance = this->location() - p->location();

			auto length = distance.x() * distance.x() + distance.y()*distance.y();
			if (length <= range_of_perception() * range_of_perception()) {
				neighbours.push_back(p->location());
			}
		}
	}
	return neighbours;
}








} // namespace pigisland

} // namespace kmint
