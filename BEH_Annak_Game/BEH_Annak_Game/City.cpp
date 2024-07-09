#include "City.h"
#include "CommonHeaders.h"
#include "Village.h"
#include "Road.h"

City::City(Position pos)
{
	this->pos = pos;
	resources = { 0, 0, 0, 0, 5 };//TODO: read from json
}

int City::count = 0;

bool City::build(shared_ptr<WorldMap> world)
{
	if(checkIfCanBuild(world)){
		count++;
		return world->addEntity(pos, make_shared<City>(*this), 20);
	}
	return false;
}
bool City::checkIfCanBuild(shared_ptr<WorldMap> world)
{
	for (int i = pos.first; i < 20 + pos.first; i++)
		for (int j = pos.second; j < 20 + pos.second; j++)
			if (dynamic_pointer_cast<Road>(world->getCoordination(pos).entity) || //TODO : check if next to road or city etc.
				dynamic_pointer_cast<City>(world->getCoordination(pos).entity))
				return false;
	return checkIfNextToRoad(world, 20);
}