#include "kmint/pigisland/pig.hpp"
#include "kmint/math/angle.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include <cmath>
#include "kmint/pigisland/node_algorithm.hpp"

#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/shark.hpp"
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

pig::pig(math::vector2d location, kmint::map::map_graph& graph,kmint::pigisland::shark& shark, kmint::pigisland::boat& boat)
	: free_roaming_actor{ random_vector()/*location*/ }, drawable_{ *this, pig_image() }, _graph(graph), shark_(shark ), boat_(boat) {
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
  //std::cout << velocity.x() << "    " << velocity.y() << std::endl;
  
  
  move(velocity);
  handleCollision();
  //handle_collisions();
}

kmint::map::map_node* const pig::getClosestNode() const {
	double closestNodeDistance = 99999;
	kmint::map::map_node* closestNode;
	
	for (kmint::map::map_node& m : _graph) {
		if (closestNodeDistance > calculateDistance(m)) {
			closestNodeDistance = calculateDistance(m);
			closestNode = &m;
		}
	}
	

	return closestNode;
}

double pig::calculateDistance(const kmint::map::map_node& mapNode) const {
	return sqrt(pow(location().x() - mapNode.location().x(), 2) + pow(location().y() - mapNode.location().y(), 2));
}

std::vector<pig*> pig::getNeighbours(double neighbourDistance) {
	std::vector<pig*> neighbours;
	for (auto i = begin_perceived(); i != end_perceived(); ++i) {
		kmint::play::actor *ptr = &(*i);
		if (auto p = dynamic_cast<kmint::pigisland::pig*>(ptr); p) {
			//std::cout << "saw something at " << p->location().x() << ", "
			//	<< p->location().y() << "\n";
			auto& distance = this->location() - p->location();

			auto length = distance.x() * distance.x() + distance.y()*distance.y();
			if (length <= neighbourDistance * neighbourDistance) {
				neighbours.push_back(p);
			}
		}
	}
	return neighbours;
}

void pig::handleCollision() {
	for (auto i = begin_collision();i != end_collision(); ++i) {
		kmint::play::actor *ptr = &(*i);
		auto & toVector = location() - ptr->location();

		const auto & k = num_colliding_actors();
		double distance = 0;
		const auto & toVectorLength = toVector.x() * toVector.x() + toVector.y() * toVector.y();
		if (toVectorLength > 0) {
			distance = std::sqrt(toVectorLength);
			double overlap = (this->radius() + ptr->radius()) - distance;
			move(toVector / distance * overlap);
		}
	}
}





} // namespace pigisland
} // namespace kmint
