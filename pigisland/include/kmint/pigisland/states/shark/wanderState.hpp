#pragma once
#include "../state.hpp"

namespace kmint {
namespace pigisland {
class shark;
class wanderState : public state
{
public:
	wanderState(shark& shark);
	void act() override;

	wanderState() = default;
private:
	shark& _shark;
	kmint::delta_time t_passed_{};
};
}
}