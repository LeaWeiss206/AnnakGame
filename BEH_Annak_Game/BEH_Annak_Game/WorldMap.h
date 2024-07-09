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
        WorldMap(Input const & input);
        WorldMap();
        void printWorldGrid() const;
        void fillWorldGrid(Input const& input);
        vector<vector<Coordination>>& getWorldGrid();
        string getCategory(int x, int y);
        string getResource(int x, int y) const;
        string getSelectedCoordinationsLandType(int x, int y) const;
        vector<int> getSelectedCoordinationsResource(int x, int y) const;
        void startResource(Input const& input);
        void raining();
        void startPeople(Input const& input);
        void startbuild(shared_ptr<Command> command);
        Coordination getCoordination(pair<int, int> coord);
        bool addEntity(Position pos, shared_ptr<IEntity> entity, int size);
};






















