#pragma once
#include "IWaitingCommand.h"
#include "CommonHeaders.h"
#include "IBuildableEntity.h"
class BuildCommand : public IWaitingCommand
{
	shared_ptr<WorldMap> world;
	shared_ptr<IBuildableEntity> entity;
	//int size;
	Position pos;
	
public:
	BuildCommand(shared_ptr<Command> command, shared_ptr<WorldMap> world);
	virtual bool execute();
};

