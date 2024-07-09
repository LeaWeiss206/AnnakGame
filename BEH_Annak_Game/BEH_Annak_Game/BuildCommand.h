#pragma once
#include "IWaitingCommand.h"
#include "CommonHeaders.h"
class BuildCommand : public IWaitingCommand
{
	WorldMap world;
	IBuildableEntity* entity;
	int size;
	Position pos;
	
public:
	BuildCommand(Command command, WorldMap& world);
	virtual bool execute();
};

