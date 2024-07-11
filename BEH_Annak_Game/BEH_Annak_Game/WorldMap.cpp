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

void WorldMap::startResource(Input const& input, shared_ptr<Command> command)
{
    int resourceAmount = stoi(command->arguments[0]), resourceIndex;
    string resourceName = command->arguments[1];
    int y = stoi(command->arguments[2]) - 1, x = stoi(command->arguments[3]) - 1;
    string landType;
    Position pos(x, y);
    if (worldGrid[x][y].entity) {
        //TODO: read from json, get the resource index by resource name
        if (resourceName == "Wood")
            resourceIndex = 0;
        else if (resourceName == "Wool")
            resourceIndex = 1;
        else if (resourceName == "Iron")
            resourceIndex = 2;
        else if (resourceName == "Blocks")
            resourceIndex = 3;
        else
            resourceIndex = 4;
        worldGrid[x][y].entity->addResources(resourceIndex, resourceAmount);
        return;
    }
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
    int i = 0;
    for (int resource : resources) {
        if (i == 4)
            break;
        result += to_string(resource);
        result += ' ';
        i++;
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

//void WorldMap::startPeople(Input const& input)
//{
//    int peopleAmount = 1;
//    int y = stoi(input.start[1]->arguments[1]) - 1, x = stoi(input.start[1]->arguments[2]) - 1;
//    string landType;
//    landType = getSelectedCoordinationsLandType(x, y);
//    if (landType == "Water")
//    {
//        //TODO:  throw exception
//        cout << "can't put a person in water " << endl;
//        return;
//    }
//    if (worldGrid[x][y].entity == nullptr)
//        worldGrid[x][y].entity.reset(new Person());
//}

void WorldMap::addPeople(shared_ptr<Command> command)
{
    int peopleAmount = stoi(command->arguments[0]), y = stoi(command->arguments[1]) - 1, x = stoi(command->arguments[2]) - 1;
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

    else if (dynamic_pointer_cast<City>(worldGrid[x][y].entity) ||
        dynamic_pointer_cast<Village>(worldGrid[x][y].entity))
        worldGrid[x][y].entity->addResources(4, peopleAmount);

}

int WorldMap::getSelectedPeople(Position pos)
{
    vector<int> resources = getSelectedCoordinationsResource(pos.first, pos.second);
    return resources[4];
}

void WorldMap::deposit(shared_ptr<Command> command, Position selectedCoordination)
{
    Position pos(stoi(command->arguments[1]) - 1, stoi(command->arguments[0]) - 1);
    if (getCoordination(pos).entity)
        for (int i = 0; i < getCoordination(selectedCoordination).entity->getResources().size() - 1; i++) {
            if (getCoordination(selectedCoordination).entity->getResources()[i] > 0)
                getCoordination(pos).entity->addResources(i, getCoordination(selectedCoordination).entity->getResources()[i]);
        }
    else
        getCoordination(pos).tile->addResources(getCoordination(selectedCoordination).entity->getResources()[getCoordination(pos).tile->landTypeNumber - 3]);
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

void WorldMap::makeEmpty(shared_ptr<Command> command)
{
    Position pos;
    pos.first = stoi(command->arguments[1]) - 1;
    pos.second = stoi(command->arguments[0]) - 1;
    if (getCoordination(pos).entity)
        getCoordination(pos).entity->emptyResources();
    else
        getCoordination(pos).tile->emptyResources();
}

//////////////////////////////////////////////////////////////////////////////////////


#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

string WorldMap::parse_to_img_path(int num)
{
    string img_path = "C:\\Users\\1\\Desktop\\annakImages\\TILES\\";
    img_path += to_string(num);
    img_path += ".png";
    return img_path;
}
Mat result;
void WorldMap::printImg()
{
    vector<Mat> rows;
    for (const auto& rowPaths : worldGrid){
        vector<Mat> images;
        for (const auto& imagePath : rowPaths) {
            Mat img = imread(parse_to_img_path(imagePath.tile->landTypeNumber));
            if (img.empty()) {
                std::cerr << "Error reading image from path: " << parse_to_img_path(imagePath.tile->landTypeNumber) << std::endl;
                return;
            }
            resize(img, img, Size(50, 50));
            images.push_back(img);
        }
        cv::Mat row;
        cv::hconcat(images, row);
        rows.push_back(row);
    }
    //Mat result;
    vconcat(rows, result);
    imshow("Image Grid", result);
    waitKey(0);
}

//void WorldMap::drawGridLines()
//{
//    //void drawGridLines(cv::Mat & image, int numRows, int numCols)
//    //{ // חישוב גודל תא הרשת
//        //int cellWidth = image.cols / numCols;
//        //int cellHeight = image.rows / numRows;
//        //// שרטוט קווים אופקיים לרשת
//        // for (int i = 1; i < numRows; ++i) {
//        //  cv::line(image, cv::Point(0, i * cellHeight), cv::Point(image.cols, i * cellHeight), cv::Scalar(255, 0, 0), 2);
//        //  }
//        //// שרטוט קווים אנכיים לרשת
//        // for (int j = 1; j < numCols; ++j) {
//        //  cv::line(image, cv::Point(j * cellWidth, 0), cv::Point(j * cellWidth, image.rows), cv::Scalar(255, 0, 0), 2);
//        ////  } 
//        //// הצגת התמונה עם הרשת 
//        // cv::imshow("Image Grid with Grid Lines", image); cv::waitKey(0);
//        //  } 
//        //// int main() { // דוגמה למטריצה של נתיבי תמונות std::vector<std::vector<std::string>> imagePaths = { {"path/to/image1.png", "path/to/image2.png"}, {"path/to/image3.png", "path/to/image4.png"} }; // קריאה לפונקציה שמציגה את המטריצה של התמונותdisplayImageGrid(imagePaths); return 0; }
//
//
//
//    vector<Mat> rows;
//    Point p1, p2;
//    for (int i = 0; i<worldGrid.size(); i+=5){
//        p1.x = (i*50);
//        p2.x == (i + worldGrid.size()-1)*50;
//        for (int j = 0; j < worldGrid[i].size(); j += 5){
//            p1.y = j*50;
//            p2.y =( j + worldGrid[i].size() - 1)*50;
//            line(result, p1, p2, Scalar(255, 0, 0), 2, LINE_8);
//            //line(result, p2, p1, Scalar(255, 0, 0), 2, LINE_8);
//        }
//    }
//    imshow("Image Grid", result);
//    waitKey(0);
//}