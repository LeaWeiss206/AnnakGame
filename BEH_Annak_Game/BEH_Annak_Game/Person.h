#pragma once
#include "IEntity.h"
#include "IMove.h"
#include "CommonHeaders.h"
class Person : public IEntity, public IMove
{
	double stepPart;
	/*int x;
	int y;*/
	public:
		Person();
		Person(Person & p);
		double getStepPart() const;
		virtual double getSpeed();
		virtual bool move(Coordination coord);
		void work(/*shared_ptr<IEntity> person, */Coordination coord);
		vector<Position> generateWay(Position& src, Position& dest);

};

