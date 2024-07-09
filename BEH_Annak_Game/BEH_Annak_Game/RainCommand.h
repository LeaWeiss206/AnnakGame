#pragma once
#include "IWaitingCommand.h"
#include "WorldMap.h"
class RainCommand : public IWaitingCommand
{
		WorldMap world;
		int rain;
	public:
		RainCommand(int rain, WorldMap & world);
		virtual bool execute();
};

