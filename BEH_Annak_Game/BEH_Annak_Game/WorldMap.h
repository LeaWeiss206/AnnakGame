#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Input.h"
//#include "NaturalLand.h"
#include "Coordination.h"
using namespace std;


class WorldMap{
    private:
        vector<vector<Coordination>> worldGrid;
        
    public:
        //int rain;
        WorldMap(Input const  & input);
        WorldMap();
        void printWorldGrid() const;
        void fillWorldGrid(Input const& input);
        string getCategory(int x, int y) const;
        string getResource(int x, int y) const;
        string getSelectedCoordinationsLandType(int x, int y) const;
        vector<int> getSelectedCoordinationsResource(int x, int y) const;
        void startResource(Input const& input);
        void raining();
        void startPeople(Input const& input);
        void startbuild(Command command);
        Coordination getCoordination(pair<int, int> coord);
        void addEntity(Position pos, IEntity* entity, int size);
};






















