#pragma once
#include "IBuildableEntity.h"
class City :public IBuildableEntity
{
	public:
		City(Position pos);
		static int count;
		virtual bool build(shared_ptr<WorldMap> world);
		virtual bool checkIfCanBuild(shared_ptr<WorldMap> world);
};

