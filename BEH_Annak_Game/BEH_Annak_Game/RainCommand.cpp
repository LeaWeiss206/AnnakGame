#include "RainCommand.h"

RainCommand::RainCommand(int rain, shared_ptr<WorldMap> world) :rain(rain), world(world)
{
}

bool RainCommand::execute()
{
	world->raining();
	return false;
}
