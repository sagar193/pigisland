#pragma once
#include "../state.hpp"

namespace kmint {
namespace pigisland {
class shark;
class fleeState : public state
{
public:
	fleeState(kmint::pigisland::shark& shark);
	void act() override;

	fleeState() = default;
private:
	kmint::pigisland::shark& _shark;
	int _fleeCounter;
};
}
}