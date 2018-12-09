#pragma once

#include "kmint/primitives.hpp"
class State
{
public:
	virtual void act(kmint::delta_time dt) = 0;
private:

};
