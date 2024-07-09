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
