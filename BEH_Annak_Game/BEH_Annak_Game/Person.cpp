#include "Person.h"

Person::Person()
{
	resources = { 0, 0, 0, 0 };
    stepPart = 0;
}

Person::Person(Person& p)
{
    this->resources[0] = p.resources[0];
    this->resources[1] = p.resources[1];
    this->resources[2] = p.resources[2];
    this->resources[3] = p.resources[3];

    this->stepPart = p.stepPart;
}

double Person::getStepPart() const
{
    return stepPart;
}

double Person::getSpeed()
{
    //todo get from json
    return 0.01;
}

int Person::getPosition()
{
	return 0;
}

vector<int> Person::getResources()
{
	return vector<int>();
}

bool Person::move(Coordination coord)
{
	//if (coord.entity != nullptr){

	//	coord.entity.reset(this);
	//	return true;
	//}
    stepPart += getSpeed();
    if (stepPart == 1.0000000000000007){
        if (coord.entity == nullptr) {
       //     coord.entity.reset(this);
            stepPart = 0;
            return true;
        }
        else {
            stepPart -= getSpeed();
        }            
    }
	return false;
}
void Person::work(/*shared_ptr<IEntity> person,*/ Coordination coord)
{
    if (coord.tile->landType != "Ground") {
        if (coord.tile->resources[coord.tile->landTypeNumber - 3] > 0) {
            coord.tile->resources[coord.tile->landTypeNumber - 3]--;
            this->resources[coord.tile->landTypeNumber - 3]++;
        }
    }
    //TODO
    //return false;
}
vector<Position> Person::generateWay(Position& src, Position& dest) {
    //check if we have to do BFS here
    vector<Position> way;
    int dx = dest.first - src.first;
    int dy = dest.second - src.second;
    if (abs(dx) >= abs(dy))
        for (int x = src.first; ; dx < 0 ? x-- : x++) {
            way.push_back({ x, src.second + dy * (x - src.first) / dx });
            if (x == src.first + dx)
                break;
        }
    else
        for (int y = src.second; ; dy < 0 ? y-- : y++) {
            way.push_back({ src.first + dx * (y - src.second) / dy, y });
            if (y == src.second + dy)
                break;
        }
    return way;
}
