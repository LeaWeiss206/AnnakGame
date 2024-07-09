#pragma once
#include "IWaitingCommand.h"
#include "WorldMap.h"
#include "IMove.h"
#include <vector>
#include "CommonHeaders.h"
#include "Person.h"
using namespace std;

class MoveCommand : public IWaitingCommand
{
	private:
		shared_ptr<WorldMap> world;
		shared_ptr<IMove> movingItem;
		Position src;
		Position dest;
		vector<Position> way;
		int currentDest;
//		void (*commandToRunAfterMoving)(Position);
		
	public:
		typedef void (Person::* FunctionPtr)(shared_ptr<IEntity> entity, Coordination coord);
		MoveCommand(shared_ptr<WorldMap> world, Position & src, Position & dest);
	//	MoveCommand(WorldMap& world, Position& src, Position& dest, FunctionPtr);
		virtual bool execute();
	//	FunctionPtr commandToRunAfterMoving;
};

