#pragma once
#include "../state.hpp"
#include "../../aStar.hpp"

namespace kmint {
namespace pigisland {
class shark;
class tiredState : public state
{
public:
	tiredState(shark& shark);
	void act() override;

	tiredState() = default;
private:
	shark& _shark;
	aStar _aStar;
	const kmint::map::map_node &find_shark_node(const kmint::map::map_graph &graph);

};
}}