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

pig::pig(math::vector2d location,
	double wanderForce, double allignmentForce, double sepArationForce, double cohessionForce, double attractionToShark, double attractionToBoat
	, kmint::map::map_graph& graph, kmint::pigisland::shark& shark, kmint::pigisland::boat& boat)
	: free_roaming_actor{ random_vector()/*location*/ }, drawable_{ *this, pig_image() }, _graph(graph), shark_(shark ), boat_(boat) {
	dna_[WANDER] = wanderForce;
	dna_[SEPARATION] = sepArationForce;
	dna_[COHESSION] = cohessionForce;
	dna_[ALLIGNMENT] = allignmentForce;
	dna_[ATTRACTIONTOSHARK] = attractionToShark;
	dna_[ATTRACTIONTOBOAT] = attractionToBoat;

}

void pig::act(delta_time dt) {
	if (alive_) {
		free_roaming_actor::act(dt);

		//Calculate forces
		const auto& steering_force = steeringBehavior->CalculateForces(*this);
		const auto& acceleration = steering_force / mass;

		//Add new acceleration to velocity
		velocity += acceleration * to_seconds(dt);

		const auto& velocity_length = (velocity.x()*velocity.x()) + (velocity.y()*velocity.y());
		if (velocity_length > 0) {
			const auto newHeading = velocity / std::sqrt(velocity_length);
			heading = newHeading;
			if (velocity_length > maxSpeed*maxSpeed) {
				velocity = newHeading * maxSpeed;
			}
		}

		move(velocity);
		die();
	}
}

map::map_node* const pig::getClosestNode() const {
	double closestNodeDistance = 99999;
	map::map_node* closestNode;
	for (map::map_node& m : _graph) {
		if (closestNodeDistance > calculateDistance(m)) {
			closestNodeDistance = calculateDistance(m);
			closestNode = &m;
		}
	}
	return closestNode;
}

void pig::die()
{
	for (auto i = begin_collision();i != end_collision(); ++i) {
		actor *ptr = &(*i);
		if (auto b = dynamic_cast<boat*>(ptr); b) {
			alive_ = false;
			//drawable_.set_tint(kmint::graphics::colors::black);
		}
		else if (auto s = dynamic_cast<shark*>(ptr);s)
		{
			alive_ = false;
			//drawable_.set_tint(kmint::graphics::colors::black);
		}
	}
}


double pig::calculateDistance(const kmint::map::map_node& mapNode) const {
	return sqrt(pow(location().x() - mapNode.location().x(), 2) + pow(location().y() - mapNode.location().y(), 2));
}

std::vector<pig*> pig::getNeighbours() {
	std::vector<pig*> neighbours;
	for (auto i = begin_perceived(); i != end_perceived(); ++i) {
		actor *ptr = &(*i);
		if (auto p = dynamic_cast<pig*>(ptr); p) {
			//auto& distance = this->location() - p->location();
			//const auto& dot = kmint::math::dot(heading, kmint::math::normalize(distance));
			//if(dot>=0)
			//{
				neighbours.push_back(p);
			//}
		}
	}
	return neighbours;
}

void pig::handleCollision() {
	for (auto i = begin_collision();i != end_collision(); ++i) {
		actor *ptr = &(*i);
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
