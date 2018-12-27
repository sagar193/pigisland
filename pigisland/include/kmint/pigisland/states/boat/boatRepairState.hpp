#pragma once
#include "../state.hpp"

namespace kmint {
namespace pigisland {
class boat;
class boatRepairState : public state
{
public:
	boatRepairState(kmint::pigisland::boat& boat);
	void act() override;

	boatRepairState() = default;
private:
	kmint::pigisland::boat& _boat;
};
}
}