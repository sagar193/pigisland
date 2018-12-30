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
#include "kmint/pigisland/wall.hpp"
#include "kmint/pigisland/island.hpp"

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
	double wanderForce, double alignmentForce, double separationForce, double cohesionForce, double attractionToShark, double attractionToBoat
	, map::map_graph& graph, shark& shark, boat& boat)
	: free_roaming_actor{ /*random_vector()*/location }, drawable_{ *this, pig_image() }, _graph(graph), shark_(shark ), boat_(boat) {
	dna_[WANDER] = wanderForce;
	dna_[SEPARATION] = separationForce;
	dna_[COHESION] = cohesionForce;
	dna_[ALIGNMENT] = alignmentForce;
	dna_[ATTRACTIONTOSHARK] = attractionToShark;
	dna_[ATTRACTIONTOBOAT] = attractionToBoat;

}

void pig::act(delta_time dt) {
	if (alive_) {
		free_roaming_actor::act(dt);
		checkCollision(dt);
		//Calculate forces
		const auto& steering_force = steeringBehavior->CalculateForces(*this);
		const auto& acceleration = steering_force / mass;

		//Add new acceleration to velocity
		velocity += acceleration * to_seconds(dt);

		const auto& velocity_length = (velocity.x()*velocity.x()) + (velocity.y()*velocity.y());
		if (velocity_length > 0) {
			const auto newHeading = velocity / std::sqrt(velocity_length);
			heading_ = newHeading;
			if (velocity_length > maxSpeed*maxSpeed) {
				velocity = newHeading * maxSpeed;
			}
		}
		move(velocity);
		
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
		if (dynamic_cast<boat*>(ptr)) {
			alive_ = false;
			//drawable_.set_tint(kmint::graphics::colors::black);
		}
		else if (dynamic_cast<shark*>(ptr))
		{
			alive_ = false;
			//drawable_.set_tint(kmint::graphics::colors::black);
		}
	}
}


double pig::calculateDistance(const kmint::map::map_node& mapNode) const {
	return sqrt(pow(location().x() - mapNode.location().x(), 2) + pow(location().y() - mapNode.location().y(), 2));
}

const std::vector<const pig*> pig::getNeighbours() {
	std::vector<const pig*> neighbours;
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

void pig::checkCollision(delta_time dt) {
	for (auto i = begin_collision();i != end_collision(); ++i) {
		actor *ptr = &(*i);
		auto toVector = location() - ptr->location();
		if (dynamic_cast<boat*>(ptr)) {
			alive_ = false;
			//drawable_.set_tint(kmint::graphics::colors::black);
		}
		else if (dynamic_cast<shark*>(ptr))
		{
			alive_ = false;
			//drawable_.set_tint(kmint::graphics::colors::black);
		}
		else if (auto w = dynamic_cast<wall*>(ptr);w) {
			//auto halfWidth = w->getLength() / 2.0;
			switch (w->getFace())
			{
			case wall::NORTH:
				if (location().y() > w->location().y())
				{
					velocity += math::vector2d(0,w->location().y() - location().y());
					//move(math::vector2d(0, -1 * maxSpeed));
				}
				break;
			case wall::SOUTH:
				if (location().y() < w->location().y())
				{
					velocity += math::vector2d(0, w->location().y() - location().y());
					//move(math::vector2d(0, maxSpeed));
				}
				break;
			case wall::WEST:
				if (location().x() > w->location().x())
				{
					velocity += math::vector2d(w->location().x()-location().x(), 0);
					//move(math::vector2d(-1 * maxSpeed, 0));
				}
				break;
			case wall::EAST:
				if (location().x() < w->location().x())
				{
					velocity += math::vector2d(w->location().x() - location().x(), 0);
					//move(math::vector2d(maxSpeed, 0));
				}
				break;
			}
		}
		else if (dynamic_cast<island*>(ptr)){
			const auto & k = num_colliding_actors();
			double distance = 0;
			const auto & toVectorLength = toVector.x() * toVector.x() + toVector.y() * toVector.y();
			if (toVectorLength > 0) {
				distance = std::sqrt(toVectorLength);
				const double overlap = (this->radius() + ptr->radius()) - distance;
				auto handleVector = toVector / distance * overlap;
				//move(normalize(handleVector)*maxSpeed*to_seconds(dt));
				//heading_ = normalize(handleVector);
				velocity += handleVector;
			}
		} else
		{
			const auto & k = num_colliding_actors();
			double distance = 0;
			const auto & toVectorLength = toVector.x() * toVector.x() + toVector.y() * toVector.y();
			if (toVectorLength > 0) {
				distance = std::sqrt(toVectorLength);
				const double overlap = (this->radius() + ptr->radius()) - distance;
				auto handleVector = toVector / distance * overlap;
				//move(normalize(handleVector)*maxSpeed*to_seconds(dt));
				//heading_ = normalize(handleVector);
				velocity += handleVector;
			}
		}
	}
}





} // namespace pigisland
} // namespace kmint
