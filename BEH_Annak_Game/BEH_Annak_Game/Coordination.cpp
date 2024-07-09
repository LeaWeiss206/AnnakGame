#include "Coordination.h"

Coordination::Coordination(shared_ptr<NaturalLand> tile)
{
	this->tile=tile;
	this->entity = nullptr;
}

bool Coordination::operator!=(Coordination const& coord) const
{
	return false;
}
