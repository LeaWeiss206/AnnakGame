#include "WaitingCommands.h"


void WaitingCommands::addCommand(shared_ptr<IWaitingCommand> command)
{
	this->commands.push_back(command);
}

void  WaitingCommands::runCommands(WorldMap & world, int wait)
{
	while (wait > 0){
		int i = 0;
		for (shared_ptr<IWaitingCommand> command : commands) {
			if (command->execute())
				commands.erase(commands.begin() + i);
			i++;
		}
		if(wait==405)
		{ }
		wait--;
	}	
}