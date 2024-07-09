#pragma once
#include <vector>
using namespace std;

class IEntity
{
	public:
		virtual int getPosition() = 0;
		virtual vector<int> getResources() = 0;
};

