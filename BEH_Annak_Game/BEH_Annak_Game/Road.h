#pragma once
#include "IBuildableEntity.h"

class Road :public IBuildableEntity
{	
	public:
		Road(Position pos);
		static int count;
		virtual bool build(shared_ptr<WorldMap> world);
		virtual bool checkIfCanBuild(shared_ptr<WorldMap> world);
		virtual bool checkIfNextToRoad(shared_ptr<WorldMap> world, int size);

};

