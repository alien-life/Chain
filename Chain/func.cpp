#include "pch.h"

void funcs::chainDashRight(int forward, int airRollRight, int jump, bool hasController)
{	
	//hold forward
	//if (hasController)
	{
		keybd_event(forward, 0, KEYEVENTF_EXTENDEDKEY, 0);
	}
	
	//hold air roll
	keybd_event(airRollRight, 0, KEYEVENTF_EXTENDEDKEY, 0);
	//jump 1
	keybd_event(jump, 0, KEYEVENTF_EXTENDEDKEY, 0);
	std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));
	keybd_event(jump, 0, KEYEVENTF_KEYUP, 0);

	keybd_event(jump, 0, KEYEVENTF_EXTENDEDKEY, 0);
	std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));
	keybd_event(jump, 0, KEYEVENTF_KEYUP, 0);

	//sleep
	std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));

	//jump 2
	keybd_event(jump, 0, KEYEVENTF_EXTENDEDKEY, 0);
	std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));
	keybd_event(jump, 0, KEYEVENTF_KEYUP, 0);

	keybd_event(jump, 0, KEYEVENTF_EXTENDEDKEY, 0);
	std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));
	keybd_event(jump, 0, KEYEVENTF_KEYUP, 0);

	//release air roll
	keybd_event(airRollRight, 0, KEYEVENTF_KEYUP, 0);
	//release forward
	if (hasController)
	{
		keybd_event(forward, 0, KEYEVENTF_KEYUP, 0);
	}
	

	
	std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));
}
void funcs::chainDashLeft(int forward, int airRollLeft, int jump, bool hasController)
{
	//hold forward
	//if (hasController)
	{
		keybd_event(forward, 0, KEYEVENTF_EXTENDEDKEY, 0);
	}
	
	//hold air roll
	keybd_event(airRollLeft, 0, KEYEVENTF_EXTENDEDKEY, 0);
	//jump 1
	keybd_event(jump, 0, KEYEVENTF_EXTENDEDKEY, 0);
	std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));
	keybd_event(jump, 0, KEYEVENTF_KEYUP, 0);

	keybd_event(jump, 0, KEYEVENTF_EXTENDEDKEY, 0);
	std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));
	keybd_event(jump, 0, KEYEVENTF_KEYUP, 0);

	//sleep
	std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));

	//jump 2
	keybd_event(jump, 0, KEYEVENTF_EXTENDEDKEY, 0);
	std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));
	keybd_event(jump, 0, KEYEVENTF_KEYUP, 0);

	keybd_event(jump, 0, KEYEVENTF_EXTENDEDKEY, 0);
	std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));
	keybd_event(jump, 0, KEYEVENTF_KEYUP, 0);

	//release air roll
	keybd_event(airRollLeft, 0, KEYEVENTF_KEYUP, 0);
	//release forward
	if (hasController)
	{
		keybd_event(forward, 0, KEYEVENTF_KEYUP, 0);
	}
	

	std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));
}
void funcs::stall(int steerRight, int airRollLeft, int jump, bool hasController)
{
	//press air roll left
	keybd_event(airRollLeft, 0, KEYEVENTF_EXTENDEDKEY, 0);
	//press steer
	keybd_event(steerRight, 0, KEYEVENTF_EXTENDEDKEY, 0);

	//jump
	keybd_event(jump, 0, KEYEVENTF_EXTENDEDKEY, 0);
	std::this_thread::sleep_for(std::chrono::microseconds(21000));
	keybd_event(jump, 0, KEYEVENTF_KEYUP, 0);

	//release air roll left
	keybd_event(airRollLeft, 0, KEYEVENTF_KEYUP, 0);
	//release steer
	keybd_event(steerRight, 0, KEYEVENTF_KEYUP, 0);

	std::this_thread::sleep_for(std::chrono::microseconds(50000));


}

