#include "pch.h"
#include "Chain.h"
#include "glfw3.h"
#include "glfw3native.h"

BAKKESMOD_PLUGIN(Chain, "Chaindash on wall", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void Chain::onLoad()
{
	//variables
	_globalCvarManager = cvarManager;
	cvarManager->log("Chain loaded!");
	
	//initialize glfw
	glfwInit();

	//checks if joystick 0 is connected
	//why did i do it like this
	if (glfwJoystickPresent(GLFW_JOYSTICK_1))
	{
		cvarManager->log("Controller detected :)");
		useController = true;
		
		//maps settings
		SettingsWrapper settings = gameWrapper->GetSettings();
		std::vector<std::pair<std::string, std::string>> binds = settings.GetAllPCBindings();
		
		controlArr[0] = (char)binds.at(0).first[0]; //forward key into int
		controlArr[1] = (char)binds.at(2).first[0]; //steer right
		controlArr[2] = (char)binds.at(12).first[0];//air roll right
		controlArr[3] = (char)binds.at(13).first[0];//air roll left
		controlArr[4] = (char)binds.at(15).first[0];//jump
		
	}
	else
	{
		useController = false;
		SettingsWrapper settings = gameWrapper->GetSettings();
		std::vector<std::pair<std::string, std::string>> binds = settings.GetAllPCBindings();

		controlArr[0] = (char)binds.at(0).first[0]; //forward key into int
		controlArr[1] = (char)binds.at(2).first[0]; //steer right
		controlArr[2] = (char)binds.at(12).first[0];//air roll right
		controlArr[3] = (char)binds.at(13).first[0];//air roll left
		controlArr[4] = (char)binds.at(15).first[0];//jump
	}
	
	//starts thread and hooks every frame you are playing
	t = this->startT();
	gameWrapper->HookEvent("Function TAGame.Car_TA.SetVehicleInput",
		[&](std::string eventName) {
			car = gameWrapper->GetLocalCar();
			roll = car.GetRotation().Roll;
			isOnWall = car.IsOnWall();
			isOnGround = car.IsOnGround();
			hasFlip = car.HasFlip();
		});
}

void Chain::gameLoop()
{	
	while (looping)
	{
		if (car)
		{
			//could reorganize this
			if (glfwJoystickPresent(GLFW_JOYSTICK_1))
			{
				int buttonCount;
				const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

				if (buttons[2] == GLFW_PRESS)
				{
					if (isOnWall && (roll < 0))
					{
						cvarManager->log("Chain dash right");
						//air roll right if < 0
						func.chainDashRight(controlArr[0], controlArr[2], controlArr[4], useController);

					}
					else if (isOnWall && (roll > 0))
					{
						cvarManager->log("Chain dash left");
						//air roll left if > 0
						func.chainDashLeft(controlArr[0], controlArr[3], controlArr[4], useController);


					}
					else if (!isOnGround && !isOnWall /* && hasFlip*/)
					{
						//hasflip doesnt work in game must patch binary
						cvarManager->log("Stall");
						//stall if not on ground and not on wall and has flip
						func.stall(controlArr[1], controlArr[3], controlArr[4], useController);
					}

				}
			}
			else
			{
				//set to f by default
				if (GetAsyncKeyState(0x46))
				{
					if (isOnWall && (roll < 0))
					{
						cvarManager->log("Chain dash right");
						//air roll right if < 0
						func.chainDashRight(controlArr[0], controlArr[2], controlArr[4], useController);
						//worker = std::thread(&funcs::chainDashRight, func, controlArr[0], controlArr[2], controlArr[4]);

					}
					else if (isOnWall && (roll > 0))
					{
						cvarManager->log("Chain dash left");
						//air roll left if > 0
						func.chainDashLeft(controlArr[0], controlArr[3], controlArr[4], useController);


					}
					else if (!isOnGround && !isOnWall /* && hasFlip*/ )
					{
						cvarManager->log("Stall");
						//stall if not on ground and not on wall and has flip
						func.stall(controlArr[1], controlArr[3], controlArr[4], useController);
					}

				}
			
			}
			
		}
	}
	
}

void Chain::testing()
{
	while (looping)
	{
		//cvarManager->log("inside");
		if (car)
		{
			int buttonCount;
			const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
			if (buttons[2] == GLFW_PRESS)
			{
				cvarManager->log("IsOnWall: " + std::to_string(isOnWall));
				cvarManager->log("isOnGround: " + std::to_string(isOnGround));
				cvarManager->log("Car Roll: " + std::to_string(roll));

				std::this_thread::sleep_for(std::chrono::milliseconds(50));
			}
			
		}

		//std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	
	
	while (true)
	{
		CarWrapper car = gameWrapper->GetLocalCar();
		if (car)
		{
			std::string roll = std::to_string(car.GetRotation().Roll);
			cvarManager->log(roll);
		}
		else
		{
			cvarManager->log("Car is NULL");
		}
	}
	
	
}


std::thread Chain::startT()
{
	return std::thread(&Chain::gameLoop, this);
}

void Chain::onUnload()
{
	//unload everything
	looping = false;
	t.join();
	glfwTerminate();
}

