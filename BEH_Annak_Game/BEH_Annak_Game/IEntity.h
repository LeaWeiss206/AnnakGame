#pragma once
#include <vector>
#include "CommonHeaders.h"
using namespace std;

class IEntity
{
	protected:
		Position pos;
		vector<int> resources;
		vector<int> maxCapacities;
	public:
		IEntity();
		virtual Position getPosition();
		virtual vector<int> getResources();
		virtual void emptyResources();
		virtual void addResources(int resourceIndex, int amount);
};

