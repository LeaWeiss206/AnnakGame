#include "Village.h"
#include "City.h"
#include "Road.h"

Village::Village(Position pos)
{
    this->pos = pos;
    resources = { 0, 0, 0, 0, 1 };
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
	for (int i = pos.first; i < 10 + pos.first; i++)
		for (int j = pos.second; j < 10 + pos.second; j++)
			if (dynamic_pointer_cast<Road>(world->getCoordination(pos).entity)|| //TODO : check if next to road or city etc.
				dynamic_pointer_cast<City>(world->getCoordination(pos).entity)||
				dynamic_pointer_cast<Village>(world->getCoordination(pos).entity))
				return false;
	return checkIfNextToRoad(world, 10);
}