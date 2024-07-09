#include "BuildCommand.h"
#include "Command.h"
#include "City.h"
#include "Village.h"
#include "Road.h"
#include "WorldMap.h"

BuildCommand::BuildCommand(Command command, WorldMap & world):entity(), world(world)
{
    pos.first = stoi(command.arguments[1]) - 1;
    pos.second = stoi(command.arguments[0]) - 1;
    if (command.arguments[0] == "City") 
        entity = new City(pos);

    else if (command.arguments[0] == "Village") {
        entity = new Village(pos);
    }
    else if (command.arguments[0] == "Road") {
        entity = new Road(pos);
    }

}

bool BuildCommand::execute()
{
    entity.build();
   /* if(world.getCoordination(pos).tile->landType == "Ground" && (!world.getCoordination(pos).entity || world.getCoordination(pos).entity))
        
    world.addEntity(pos, entity, size);*/
    return true;
}
