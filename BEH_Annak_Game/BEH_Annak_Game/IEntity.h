#pragma once
#include <vector>
#include "CommonHeaders.h"
using namespace std;

class IEntity
{
	protected:
		Position pos;
		vector<int> resources;
	public:
		IEntity();
		virtual Position getPosition();
		virtual vector<int> getResources();
};

