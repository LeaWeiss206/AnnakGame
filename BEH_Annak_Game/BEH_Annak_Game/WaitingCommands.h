#pragma once
#include <vector>
#include <memory>
#include "IWaitingCommand.h"
#include "WorldMap.h"
using namespace std;

class WaitingCommands
{
	private:
		vector<shared_ptr<IWaitingCommand>> commands;
		vector<int> finishedCommands;
	public:
		void addCommand(shared_ptr<IWaitingCommand> command);
		void runCommands(shared_ptr<WorldMap> world, int wait);

};

