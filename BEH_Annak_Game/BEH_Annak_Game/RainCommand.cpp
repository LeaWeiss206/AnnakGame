#include "RainCommand.h"

RainCommand::RainCommand(int rain, WorldMap  & world) :rain(rain), world(world)
{
}

bool RainCommand::execute()
{
	world.raining();
	return false;
}
