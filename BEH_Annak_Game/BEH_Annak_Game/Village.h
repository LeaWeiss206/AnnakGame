#pragma once
#include "IBuildableEntity.h"
class Village :public IBuildableEntity
{
	public:
		Village(Position pos);
		static int count;
		virtual bool build(shared_ptr<WorldMap> world);
		virtual bool checkIfCanBuild(shared_ptr<WorldMap> world);
};

