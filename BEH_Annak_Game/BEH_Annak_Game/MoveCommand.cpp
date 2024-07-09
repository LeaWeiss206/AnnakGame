#include "MoveCommand.h"


MoveCommand::MoveCommand(WorldMap& world, Position& src, Position& dest/*, FunctionPtr commandToRunAfterMoving*/)
	: world(world), src(src), dest(dest)/*, commandToRunAfterMoving(commandToRunAfterMoving) */// השתמש בהפניות
{
	shared_ptr<IEntity> entity = world.getCoordination(src).entity;
	movingItem = dynamic_pointer_cast<IMove>(entity);
	way = movingItem->generateWay(src, dest);
	currentDest = 1;
	this->dest = way[currentDest++];
}



bool MoveCommand::execute()
{
	if (movingItem->move(world.getCoordination(dest))) {
		//	Position pos = src;

		world.getCoordination(dest).entity = world.getCoordination(src).entity;

		world.getCoordination(src).entity.reset();
		src = dest;
		if (currentDest == way.size() - 1) {
			shared_ptr<Person>	personPtr = std::dynamic_pointer_cast<Person>(movingItem);

			if (personPtr) {
				personPtr->work(world.getCoordination(dest));
			}
			return true;
		}
		
		dest = way[currentDest++];
	}
	//else if (movingItem->getStepPart() == 1.0 - movingItem->getSpeed()) {

	//}

	return false;
}
