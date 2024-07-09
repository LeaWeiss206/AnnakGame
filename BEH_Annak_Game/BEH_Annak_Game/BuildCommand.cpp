#include "BuildCommand.h"
#include "Command.h"
#include "City.h"
#include "Village.h"
#include "Road.h"
#include "WorldMap.h"

BuildCommand::BuildCommand(shared_ptr<Command> command, shared_ptr<WorldMap> world)/*:entity(), world(world)*/
{
    this->entity = entity;
    this->world = world;
    pos.first = stoi(command->arguments[2]) - 1;
    pos.second = stoi(command->arguments[1]) - 1;
    if (command->arguments[0] == "City") 
        entity.reset(new City(pos));

    else if (command->arguments[0] == "Village") {
        entity.reset(new Village(pos));
    }
    else if (command->arguments[0] == "Road") {
        entity.reset(new Road(pos));
    }

}

bool BuildCommand::execute()
{
    if (world->getCoordination(pos).tile->landType == "Ground")
        return entity->build(world);
    return false;
}
