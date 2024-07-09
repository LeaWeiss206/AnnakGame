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
    //printWorldGrid();
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

string WorldMap::getSelectedCoordinationsLandType(int x, int y) const
{
    string landType;
    //if (worldGrid[x][y].entity != nullptr)
    //    return 
    //else
    landType = worldGrid[x][y].tile->landType;
    return landType;
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
    //cout << "try to add  " << resourceAmount << " " << resourceName << " to " << landType << endl;
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
string WorldMap::getCategory(int x, int y) const
{
    //int resourceAmount = stoi(input.start[0]->arguments[0]);
    //string resourceName = input.start[0]->arguments[1];

    //int y = stoi(input.steps[0]->arguments[0]) - 1, x = stoi(input.steps[0]->arguments[1]) - 1;
   
    //string landType;
    return getSelectedCoordinationsLandType(x, y);
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
    int peopleAmount = 1; /*stoi(input.start[0]->arguments[0]);*/
    //string resourceName = input.start[0]->arguments[1];
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

void WorldMap::startbuild(Command command)
{
    int size;
    IEntity* entity;
    if(command.arguments[0] == "City") {
        entity = new City();
        size = 20; 
    }
    else if (command.arguments[0] == "Village") {
        entity = new Village();
        size = 10;
    }
    else if (command.arguments[0] == "Road") {
        entity = new Road();
        size = 5;
    }

    Position pos;
    pos.first = stoi(command.arguments[1]) - 1;
    pos.second = stoi(command.arguments[0]) - 1;

    addEntity(pos, entity, size);

}

Coordination WorldMap::getCoordination(pair<int, int> coord)
{
    return worldGrid[coord.first][coord.second];
}

void WorldMap::addEntity(Position pos, IEntity* entity, int size)
{
    for (int i = pos.first; i < size + pos.first; i++)
        for (int j = pos.second ; j < size + pos.second; j++)
            worldGrid[i][j].entity.reset(entity);
}
