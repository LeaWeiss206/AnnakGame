#include "IEntity.h"

IEntity::IEntity()
{
    resources = { 0, 0, 0, 0 };
    pos.first = -1;
    pos.second = -1;
}

Position IEntity::getPosition()
{
    return Position();
}

vector<int> IEntity::getResources()
{
    return resources;
}

void IEntity::emptyResources()
{
    for (int resource : resources)
        resource = 0;
}

void IEntity::addResources(int resourceIndex, int amount)
{
    int maxCapacity = maxCapacities[resourceIndex];//TODO: read from json
    resources[resourceIndex] += amount;
    if (resources[resourceIndex] > maxCapacity)
        resources[resourceIndex] = maxCapacity;
}