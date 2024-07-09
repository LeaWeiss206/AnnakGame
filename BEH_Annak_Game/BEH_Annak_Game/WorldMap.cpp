#include "WorldMap.h"
#include "Person.h"
#include "City.h"
#include "Village.h"
#include "Road.h"
#include "IEntity.h"
using namespace std;

WorldMap::WorldMap(Input const& input)
{
    fillWorldGrid(input);
}
WorldMap::WorldMap()
{
}
void WorldMap::printWorldGrid() const
{
    for(vector<Coordination> d:worldGrid)
    {
        for (Coordination coord : d)
        {
            //if (coord.entity != nullptr) {
            //    /*if (dynamic_pointer_cast<Road>(coord.entity))
            //        cout << "Road ";
            //    else if(dynamic_pointer_cast<City>(coord.entity))
            //        cout << "City ";
            //    else if (dynamic_pointer_cast<Village>(coord.entity))
            //        cout << "Village ";
            //    else if (dynamic_pointer_cast<Person>(coord.entity))
            //        cout << "Person ";*/
            //    cout << "0 ";
            //}
            //else
                cout<<coord.tile->landTypeNumber << " ";
        }
        cout<<endl;
    }   
    
}
void WorldMap::fillWorldGrid(Input const& input)
{   
    int j=0;
    for(vector<string> d: input.world->data)
    {
            for(int i=0; i<5; i++)
            worldGrid.push_back(vector<Coordination>());
            for (auto str : d)
            {
                shared_ptr<NaturalLand> tile;
                tile.reset(new NaturalLand(stoi(str)));
                Coordination coord(tile);
                for(int i=0; i<5; i++)
                    worldGrid[j].push_back(coord);
            }
            for(int i = j + 1; i<j+5;i++){
                for (int ii=0; ii <worldGrid[j].size();  ii++) {
                    worldGrid[i].push_back(worldGrid[j][ii]);
                }
            }
            j+=5;
    } 
}

vector<vector<Coordination>>& WorldMap::getWorldGrid()
{
    return worldGrid;
}

string WorldMap::getSelectedCoordinationsLandType(int x, int y) const
{
    //string landType;
    //landType = worldGrid[x][y].tile->landType;
    //return landType;
    return worldGrid[x][y].tile->landType;
}
vector<int> WorldMap::getSelectedCoordinationsResource(int x, int y)const
{
    string landType;
    landType = worldGrid[x][y].tile->landType;
   
    if(landType!="Ground"|| worldGrid[x][y].entity == nullptr)
        return worldGrid[x][y].tile->resources;
    return worldGrid[x][y].entity->getResources();
}
void WorldMap::startResource(Input const& input)
{
    int resourceAmount = stoi(input.start[0]->arguments[0]);
    string resourceName = input.start[0]->arguments[1];
    int y = stoi(input.start[0]->arguments[2]) - 1, x = stoi(input.start[0]->arguments[3]) - 1;
    string landType;
    landType = getSelectedCoordinationsLandType(x, y);
    if (landType == "Ground" ||
        landType == "Water" ||
        (landType == "Forest" && resourceName != "Wood") ||
        (landType == "Field" && resourceName != "Wool") ||
        (landType == "IronMine" && resourceName != "Iron") ||
        (landType == "BlocksMine" && resourceName != "Blocks"))
    {
        //TODO:  throw exception
        cout << "can't add " << resourceName << " to " << landType << endl;
        return;
    }
    worldGrid[x][y].tile->startResource(resourceAmount);
}
string WorldMap::getCategory(int x, int y)
{
    Position pos;
    pos.first = x;
    pos.second = y;
    if (getCoordination(pos).entity == nullptr)
        return getSelectedCoordinationsLandType(x, y);
    else if (dynamic_cast<Road*>(getCoordination(pos).entity.get()))
        return "Road";
    else if (dynamic_cast<Village*>(getCoordination(pos).entity.get()))
        return "Village";
    else if (dynamic_cast<City*>(getCoordination(pos).entity.get()))
        return "City";
    else if (dynamic_cast<Person*>(getCoordination(pos).entity.get()))
        return "Person";
    return "";
}

string WorldMap::getResource(int x, int y) const
{
    vector<int> resources = getSelectedCoordinationsResource(x, y);
    string result = "";
    for (int resource : resources) {
        result += to_string(resource);
        result += ' ';
    }
    return result;
}
void WorldMap::raining()
{
    for (int j = 0; j < worldGrid.size(); j += 5) {
        for (int i = 0;j%5==0&& i < worldGrid[j].size(); i += 5) {
            if (worldGrid[j][i].tile->landType == "Forest" || worldGrid[j][i].tile->landType == "Field")
                worldGrid[j][i].tile->raining();
    }
}


}

void WorldMap::startPeople(Input const& input)
{
    int peopleAmount = 1;
    int y = stoi(input.start[1]->arguments[1]) - 1, x = stoi(input.start[1]->arguments[2]) - 1;
    string landType;
    landType = getSelectedCoordinationsLandType(x, y);
    if (landType == "Water")
    {
        //TODO:  throw exception
        cout << "can't put a person in water " << endl;
        return;
    }
    if (worldGrid[x][y].entity == nullptr)
        worldGrid[x][y].entity.reset(new Person());
}

void WorldMap::startbuild(shared_ptr<Command> command)
{
    shared_ptr<IBuildableEntity> entity;
    Position pos;
    int size = 0;
    pos.first = stoi(command->arguments[2])-1;
    pos.second = stoi(command->arguments[1])-1;

    if(command->arguments[0] == "City") {
        entity = make_shared<City>(pos);
        City::count++;
        size = 20; //TODO:  read size from json
    }
    else if (command->arguments[0] == "Village") {
        entity = make_shared<Village>(pos);
        Village::count++;
        size = 10; //TODO:  read size from json
    }
    else if (command->arguments[0] == "Road") {
        entity = make_shared<Road>(pos);
        Road::count++;
        size = 5; //TODO:  read size from json
    }
    addEntity(pos, entity, size);
}

Coordination WorldMap::getCoordination(pair<int, int> coord)
{
    return worldGrid[coord.first][coord.second];
}

bool WorldMap::addEntity(Position pos, shared_ptr<IEntity> entity, int size)
{
    for (int i = pos.first; i < size + pos.first; i++)
        for (int j = pos.second ; j < size + pos.second; j++)
            worldGrid[i][j].entity=entity;
    return true;
}
