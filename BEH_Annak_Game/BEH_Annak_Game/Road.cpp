#include "Road.h"
#include "City.h"
#include "Village.h"

Road::Road(Position pos)
{
    this->pos = pos;
    resources = { 0, 0, 0, 0, 0 };
	//maxCapacities = { 10, 10, 5, 5, 10 };//TODO: read from json
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
	return checkIfEmptyArea(world, 5)&&checkIfNextToRoad(world, 5);
}

bool Road::checkIfNextToRoad(shared_ptr<WorldMap> world, int size)
{
	Position currentPos;
	int count = 0;
	bool flag = true;
	//check right
	currentPos.second = pos.second + size;
	currentPos.first = pos.first;
	string catagory = world->getCategory(currentPos.first, currentPos.second);
	for (int i = pos.first+1; pos.second + size < world->getWorldGrid()[i].size() && i < (size + pos.first); i++) {
		currentPos.first = i;
		if (catagory != world->getCategory(currentPos.first, currentPos.second)) {//TODO : check if next to road or city etc.
			flag = false;
		}
	}
	if (flag)
		return true;

	//check left
	currentPos.second = pos.second - 1;
	currentPos.first = pos.first;
	catagory = world->getCategory(currentPos.first, currentPos.second);
	for (int i = pos.first + 1; i < (size + pos.first); i++) {
		currentPos.first = i;
		if (catagory != world->getCategory(currentPos.first, currentPos.second)) {//TODO : check if next to road or city etc.
			flag = false;
		}
	}
	if (flag)
		return true;

	//check top
	currentPos.first = pos.first-1;
	currentPos.second = pos.second;
	catagory = world->getCategory(currentPos.first, currentPos.second);
	for (int i = pos.second + 1; i < (size + pos.second); i++) {
		currentPos.second = i;
		if (catagory != world->getCategory(currentPos.first, currentPos.second)) {//TODO : check if next to road or city etc.
			flag = false;
		}
	}
	if (flag)
		return true;

	//check bottom
	currentPos.first = pos.first+5;
	currentPos.second = pos.second;
	catagory = world->getCategory(currentPos.first, currentPos.second);
	for (int i = pos.second + 1; i < (size + pos.second); i++) {
		currentPos.second = i;
		if (catagory != world->getCategory(currentPos.first, currentPos.second)) {//TODO : check if next to road or city etc.
			flag = false;
		}
	}
	if (flag)
		return true;
	return false;
}
