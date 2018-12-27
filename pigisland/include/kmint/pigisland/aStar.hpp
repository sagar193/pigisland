#pragma once
#include "kmint/pigisland/resources.hpp"


namespace kmint {
namespace pigisland {
class aStar
{
public:
	aStar();
	~aStar();
	std::vector<const kmint::map::map_node*> FindShortestPath(const kmint::map::map_node &firstNode, const kmint::map::map_node &lastNode);
private:
	float calculateDistance(const kmint::map::map_node &firstNode, const kmint::map::map_node &secondNode);
};

}
}