#pragma once
#include "IBuildableEntity.h"
class Village :public IBuildableEntity
{
public:
	virtual int getPosition();
	virtual vector<int> getResources();
	virtual bool build(WorldMap& world);
};

