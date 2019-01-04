#include "kmint/pigisland/pig.hpp"
#include "kmint/math/angle.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include <cmath>
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/SteeringBehaviors.hpp"
#include "kmint/pigisland/wall.hpp"


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
	timeAlive_ = delta_time(0);
	dna_index[0] = WANDER;
	dna_index[1] = SEPARATION;
	dna_index[2] = COHESION;
	dna_index[3] = ALIGNMENT;
	dna_index[4] = ATTRACTIONTOSHARK;
	dna_index[5] = ATTRACTIONTOBOAT;
}

void pig::act(delta_time dt) {
	if (alive_) {
		free_roaming_actor::act(dt);
		if (shark_.swimming()) {
			timeAlive_ += dt;
		}
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
	alive_ = false;
	caught_ = true;
}

void pig::spliceDNA(const pig& papa, const pig& mama)
{
	const auto cut = random_int(0, 6);
	for(int i = 0;i<6;i++)
	{
		if (i <= cut) {
			dna_[dna_index[i]] = papa.dna_.at(dna_index[i]);
			continue;
		}
		dna_[dna_index[i]] = mama.dna_.at(dna_index[i]);
	}

	const auto mutationChance = random_int(0, 101);
	if(mutationChance>=95)
	{
		if(dna_index[cut] == ATTRACTIONTOSHARK || dna_index[cut] == ATTRACTIONTOBOAT)
		{
			dna_[dna_index[cut]] = random_scalar(-1, 1);
		}
		else
		{
			dna_[dna_index[cut]] = random_scalar(0, 1);
		}
	}
}



double pig::calculateDistance(const kmint::map::map_node& mapNode) const {
	return sqrt(pow(location().x() - mapNode.location().x(), 2) + pow(location().y() - mapNode.location().y(), 2));
}



void pig::checkCollision(delta_time dt) {
	for (auto i = begin_collision();i != end_collision(); ++i) {
		actor *ptr = &(*i);
		auto toVector = location() - ptr->location();
		if (dynamic_cast<boat*>(ptr)) {
			caught_ = true;
			//drawable_.set_tint(kmint::graphics::colors::black);
		}
		
		else if (const auto w = dynamic_cast<wall*>(ptr);w) {
			//auto halfWidth = w->getLength() / 2.0;
			switch (w->getFace())
			{
			case wall::NORTH:
				if (location().y() > w->location().y())
				{
					//velocity += math::normalize(math::vector2d(0,w->location().y() - location().y()))*maxSpeed;
					move(math::vector2d(0, w->location().y() - location().y()));
					velocity = math::vector2d(velocity.x(), 0);
					
				}
				break;
			case wall::SOUTH:
				if (location().y() < w->location().y())
				{
					//velocity += math::normalize(math::vector2d(0, w->location().y() - location().y()))*maxSpeed;
					move(math::vector2d(0, w->location().y() - location().y()));
					velocity = math::vector2d(velocity.x(), 0);

				}
				break;
			case wall::WEST:
				if (location().x() > w->location().x())
				{
					//velocity += math::normalize(math::vector2d(w->location().x()-location().x(), 0))*maxSpeed;
					move(math::vector2d(w->location().x() - location().x(), 0));
					velocity = math::vector2d(0, velocity.y());
				}
				break;
			case wall::EAST:
				if (location().x() < w->location().x())
				{
					//velocity += math::normalize(math::vector2d(w->location().x() - location().x(), 0))*maxSpeed;
					move(math::vector2d(w->location().x() - location().x(), 0));
					velocity = math::vector2d(0, velocity.y());
				}
				break;
			}
		}
		else
		{
			const auto & k = num_colliding_actors();
			double distance = 0;
			const auto & toVectorLength = toVector.x() * toVector.x() + toVector.y() * toVector.y();
			if (toVectorLength > 0) {
				distance = std::sqrt(toVectorLength);
				const double overlap = (this->radius() + ptr->radius()) - distance;
				const auto handleVector = toVector / distance * overlap;
				move(handleVector);
			}
		}
	}
}

void pig::revive()
{
	alive_ = true;
	caught_ = false;
	timeAlive_ = delta_time(0);
}



} // namespace pigisland
} // namespace kmint
