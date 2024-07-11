#include "IBuildableEntity.h"
#include "Road.h"
#include "City.h"
#include "Village.h"

bool IBuildableEntity::checkIfNextToRoad(shared_ptr<WorldMap> world, int size)
{
	Position road;
	int count = 0;
	//check right

	for (int i = pos.first; pos.second + size < world->getWorldGrid()[i].size() && i < (size + pos.first - 5); i++) {
		road.second = pos.second + size;
		count = 0;
		for (int j = i; j < i + 5; j++) {
			road.first = i;
			if (dynamic_pointer_cast<Road>(world->getCoordination(road).entity))//TODO : check if next to road or city etc.
				count++;
		}
		if (count == 5)
			return true;
	}
	//check left
	if (pos.second - 1 > 0) {
		road.second = pos.second - 1;
		for (int i = pos.first; i < (size + pos.first - 5); i++){
			count = 0;
			for (int j = i; j < (i + 5); j++) {
				road.first = j;
				if (dynamic_pointer_cast<Road>(world->getCoordination(road).entity))
					count++;
			}
			if (count == 5)
				return true;
		}
	}
	//check top
	if (pos.first - 1 > 0) {
		road.first = pos.first - 1;
		for (int i = pos.second; i < (size + pos.second - 5); i++) {
			count = 0;
			for (int j = i; j < i + 5; j++) {
				road.second = j;
				if (dynamic_pointer_cast<Road>(world->getCoordination(road).entity))
					count++;
			}
			if (count == 5)
				return true;
		}
	}
	//check bottom
	if (pos.first + size < world->getWorldGrid().size()) {
		road.first = pos.first + size;
		for (int i = pos.second; i < (size + pos.second - 5); i++) {
			count = 0;
			for (int j = i; j < i + 5; j++) {
				road.second = j;
				if (dynamic_pointer_cast<Road>(world->getCoordination(road).entity))
					count++;
			}
			if (count == 5)
				return true;
		}
		return false;
	}
}

bool IBuildableEntity::checkIfEmptyArea(shared_ptr<WorldMap> world, int size)
{
	for (int i = pos.first; i < size + pos.first; i++)
		for (int j = pos.second; j < size + pos.second; j++)
			if (dynamic_pointer_cast<Road>(world->getCoordination(pos).entity) || //TODO : check if next to road or city etc.
				dynamic_pointer_cast<City>(world->getCoordination(pos).entity) ||
				dynamic_pointer_cast<Village>(world->getCoordination(pos).entity) ||
				(world->getCoordination(pos).tile->landType != "Ground"))
					return false;
}