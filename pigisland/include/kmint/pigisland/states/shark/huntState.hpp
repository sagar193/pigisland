#pragma once
#include "../state.hpp"

namespace kmint {
namespace pigisland {
class shark;
class huntState : public state
{
public:
	huntState(shark& shark);
	void act() override;

	huntState() = default;
private:
	shark& _shark;
	kmint::delta_time t_passed_{};
};
}}
