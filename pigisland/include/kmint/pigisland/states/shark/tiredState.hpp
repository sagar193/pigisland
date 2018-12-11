#pragma once
#include "../state.hpp"

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
	kmint::delta_time t_passed_{};
};
}}