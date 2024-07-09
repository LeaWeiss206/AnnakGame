#pragma once
#include <memory>
#include "NaturalLand.h"
#include "IEntity.h"
using namespace std;

class Coordination
{
public:

	shared_ptr<NaturalLand> tile;
	shared_ptr<IEntity> entity;
	Coordination(shared_ptr<NaturalLand> tile);
	bool operator !=(Coordination const& coord) const;
};

