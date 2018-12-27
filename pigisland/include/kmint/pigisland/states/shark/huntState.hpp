#pragma once
#include "../state.hpp"
#include "../../aStar.hpp"


namespace kmint {
namespace pigisland {
class shark;
class pig;
class huntState : public state
{
public:
	huntState(shark& shark);
	void act() override;

	huntState() = default;
private:
	shark& _shark;
	aStar _aStar;
	std::vector<const kmint::map::map_node*> path;

	double calculateDistance(kmint::pigisland::pig* pig);
};
}}
