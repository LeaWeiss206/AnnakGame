#pragma once
#include "IEntity.h"
#include "WorldMap.h"
class IBuildableEntity :public IEntity
{
	public:
		virtual bool build(shared_ptr<WorldMap> world)=0;
		virtual bool checkIfCanBuild(shared_ptr<WorldMap> world) = 0;
		virtual bool checkIfNextToRoad(shared_ptr<WorldMap> world, int size);
};

