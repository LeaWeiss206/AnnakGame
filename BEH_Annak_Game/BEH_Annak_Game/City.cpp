#include "City.h"
#include "CommonHeaders.h"
#include "Village.h"
#include "Road.h"

City::City(Position pos)
{
	this->pos = pos;
	resources = { 0, 0, 0, 0, 5 };//TODO: read from json
	maxCapacities = { 20, 20, 10, 10, 20 };//TODO: read from json
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
	return checkIfEmptyArea(world, 20) && checkIfNextToRoad(world, 20);
}


