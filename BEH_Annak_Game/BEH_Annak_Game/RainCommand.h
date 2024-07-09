#pragma once
#include "IWaitingCommand.h"
#include "WorldMap.h"
class RainCommand : public IWaitingCommand
{
		shared_ptr<WorldMap> world;
		int rain;
	public:
		RainCommand(int rain, shared_ptr<WorldMap> world);
		virtual bool execute();
};

