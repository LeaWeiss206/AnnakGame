#pragma once
#include "IBuildableEntity.h"

class Road :public IBuildableEntity
{
	virtual int getPosition();
	virtual vector<int> getResources();
	virtual bool build(WorldMap& world);
};

