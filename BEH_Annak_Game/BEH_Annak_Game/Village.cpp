#include "Village.h"
#include "City.h"
#include "Road.h"

Village::Village(Position pos)
{
    this->pos = pos;
    resources = { 0, 0, 0, 0, 1 };
	maxCapacities = { 10, 10, 5, 5, 10 };//TODO: read from json
}

int Village::count = 0;

bool Village::build(shared_ptr<WorldMap> world)
{
	if (checkIfCanBuild(world)) {
		Village::count++;
		return world->addEntity(pos, make_shared<Village>(*this), 10);
	}
	return false;
}

bool Village::checkIfCanBuild(shared_ptr<WorldMap> world)
{
	return checkIfEmptyArea(world, 10) && checkIfNextToRoad(world, 10);
}