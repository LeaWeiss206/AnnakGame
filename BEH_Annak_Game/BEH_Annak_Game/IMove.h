#pragma once
#include "Coordination.h"
#include "CommonHeaders.h"
class IMove
{
public:
	virtual double getStepPart() const= 0;
	virtual double getSpeed()=0;
	virtual bool move(Coordination coord)=0;
	virtual vector<Position> generateWay(Position& src, Position& dest) = 0;
};

