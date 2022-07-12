#pragma once
#include "pch.h"

class funcs
{
public:
	void chainDashRight(int forward, int airRollRight, int jump, bool hasController);
	void chainDashLeft(int forward, int airRollLeft, int jump, bool hasController);
	void stall(int steerRight, int airRollLeft, int jump, bool hasController);

	int sleepTime = 22100;

};


