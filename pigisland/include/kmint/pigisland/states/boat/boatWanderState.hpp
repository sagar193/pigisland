#pragma once
#include "../state.hpp"

namespace kmint {
namespace pigisland {
class boat;
class boatWanderState : public state
{
public:
	boatWanderState(kmint::pigisland::boat& boat);
	void act() override;

	boatWanderState() = default;
private:
	kmint::pigisland::boat& _boat;
};
}
}