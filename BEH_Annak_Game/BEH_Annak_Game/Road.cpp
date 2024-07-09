#include "Road.h"
#include "City.h"
#include "Village.h"

Road::Road(Position pos)
{
    this->pos = pos;
    resources = { 0, 0, 0, 0, 0 };
}
int Road::count = 0;

bool Road::build(shared_ptr<WorldMap> world)
{
	if (checkIfCanBuild(world)) {
		count++;
		return world->addEntity(pos, make_shared<Road>(*this), 5);
	}
	return false;
}
bool Road::checkIfCanBuild(shared_ptr<WorldMap> world)
{
	for (int i = pos.first; i < 5 + pos.first; i++)
		for (int j = pos.second; j < 5 + pos.second; j++)
			if (dynamic_pointer_cast<Road>(world->getCoordination(pos).entity) || //TODO : check if next to road or city etc.
				dynamic_pointer_cast<City>(world->getCoordination(pos).entity)||
				dynamic_pointer_cast<Village>(world->getCoordination(pos).entity))
				return false;
	return checkIfNextToRoad(world, 5);
}