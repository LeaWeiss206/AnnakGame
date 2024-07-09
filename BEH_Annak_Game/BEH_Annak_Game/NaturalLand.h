#pragma once
#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include "ReadJson.h"
#include "json.hpp"
using json = nlohmann::json;

using namespace std;


class NaturalLand
{
	public:
		string landType;
		int landTypeNumber;
		int rain;
		//int amount;
		vector<int> resources;

		NaturalLand(int landTypeNumber);
		
		static string getCategoryBySelectedValue(int categ, string category);
		int getValueBySelectedCategory(string categ, string group);
		void startResource(int addAmount);
		void raining();

};

