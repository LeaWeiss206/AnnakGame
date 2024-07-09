#include "WaitingCommands.h"


void WaitingCommands::addCommand(shared_ptr<IWaitingCommand> command)
{
	this->commands.push_back(command);
	finishedCommands.push_back(0);
}

//void  WaitingCommands::runCommands(WorldMap & world, int wait)
//{
//	while (wait > 0){
//		int i = 0;
//		//for (shared_ptr<IWaitingCommand> command : commands) {
//		while(i<commands.size()){
//			if (commands[i]->execute()) {
//				commands.erase(commands.begin() + i);
//				if (i = commands.size() - 1)
//					break;
//			}
//			else
//			    i++;
//		}
//		if(wait==405)
//		{ }
//		wait--;
//	}	
//}

void WaitingCommands::runCommands(shared_ptr<WorldMap> world, int wait) {
	while (wait > 0) {

		auto it = commands.begin();
		while (it != commands.end()){
			if (!(*it)->finished&&(*it)->execute())
				(*it)->finished = true;
			if ((*it) == nullptr)
				return;
			else
				++it;
		}
		wait--;
	}
}