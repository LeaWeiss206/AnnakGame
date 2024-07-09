#pragma once
#include "IEntity.h"
#include "WorldMap.h"
class IBuildableEntity :public IEntity
{
protected:
	Position pos;
public:

	virtual int getPosition() = 0;
	virtual vector<int> getResources() = 0;
	virtual bool build(WorldMap& world) = 0;
};

