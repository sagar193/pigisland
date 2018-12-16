#include "kmint/pigisland/pig.hpp"
#include "kmint/math/angle.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include <cmath>
#include "kmint/pigisland/node_algorithm.hpp"

namespace kmint {
namespace pigisland {

namespace {

math::vector2d random_vector() {
  auto x = random_scalar(100, 924);
  auto y = random_scalar(50, 728);
  return {x, y};
}
} // namespace

pig::pig(math::vector2d location, kmint::map::map_graph& graph)
	: free_roaming_actor{ random_vector() }, drawable_{ *this, pig_image() }, _graph(graph) {}
      

void pig::act(delta_time dt) {
  free_roaming_actor::act(dt);
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
} // namespace pigisland
} // namespace kmint
