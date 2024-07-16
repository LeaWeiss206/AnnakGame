#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include "Input.h"
#include "RainCommand.h"
#include "Command.h"
#include "WaitingCommands.h"
#include "MoveCommand.h"
#include "Person.h"
#include "BuildCommand.h"
#include "City.h"
#include "Village.h"
#include "Road.h"
#include "Graphics.h"
//#include "WorldMap.h"
using namespace std;

#ifdef _DEBUG
// the debug version that corresponds to the opencv_world420d.dll:
#pragma comment(lib, "opencv_world4100d.lib")
#else
// the release version that corresponds to the opencv_world420.dll:
#pragma comment(lib, "opencv_world4100.lib")
#endif


void runStartCommands(shared_ptr<WorldMap> world, Input const& input);
void runAssertsCommands(shared_ptr<WorldMap> world, Input const& input, pair<int, int> selectedCoordination);
void runInputCommands(shared_ptr<WorldMap> world, Input const& input);

Position selectedCoordination;
WaitingCommands waitingCommands;

int main()
{
    Input input("input.txt");
    input.parse_and_store();
    

    shared_ptr<WorldMap> world(new WorldMap(input));//WorldMap constructor fills the world grid

    runStartCommands(world, input);
    runInputCommands(world, input); 
    runAssertsCommands(world, input, selectedCoordination);

    
   /* graphics->printImg(world);
    graphics->addPersonAfterBackground("C:\\Users\\1\\Desktop\\annakImages\\People\\WALKING PERSON 1\\sprite_1.png", 10,5);*/
    //graphics.addImageAndShow("sprite_1", Position(2, 2));
    //world->drawGridLines();


    return 0;
}

void runStartCommands(shared_ptr<WorldMap> world, Input const& input)
{
    for(shared_ptr<Command> command: input.start){
        string startCommand = command->name;
        if (startCommand == Command::RESOURCE){
            //TODO: try catch
            world->startResource(input, command);
            continue;
        }
        if (startCommand == Command::PEOPLE){
            //TODO: try catch
            world->addPeople(command);
            continue;
        }
        if (startCommand == Command::BUILD) {
            world->startbuild(command);
            continue;
        }
        if (startCommand == Command::MAKE_EMPTY) {
            world->makeEmpty(command);
            continue;
        }
    }
    world->getGraphics()->moveObjectsRandomly();
}
 
void runInputCommands(shared_ptr<WorldMap> world, Input const& input)
{

    for (shared_ptr< Command> command : input.steps) {
        string inputCommand = command->name;
        if (inputCommand == Command::SELECT)
        {
            int y = stoi(command->arguments[0]) - 1, x = stoi(command->arguments[1]) - 1;
            selectedCoordination.first = x;
            selectedCoordination.second = y;
            continue;
        }
        if (inputCommand == Command::RAIN)
        {
            shared_ptr <IWaitingCommand> rain(new RainCommand(stoi(command->arguments[0]), world));
            waitingCommands.addCommand(rain);
            continue;
        }
        if(inputCommand == Command::WORK)
        {
            if (Person* p = dynamic_cast<Person*>(world->getCoordination(selectedCoordination).entity.get())){
                Position pos;
                pos.first = stoi(command->arguments[1]) - 1;
                pos.second = stoi(command->arguments[0]) - 1;
                shared_ptr<IWaitingCommand> move(new MoveCommand(world, selectedCoordination, pos));
                waitingCommands.addCommand(move);
                continue;
            }

        }
        if (inputCommand == Command::MOVE) {
            Position pos;
            pos.first = stoi(command->arguments[1]) - 1;
            pos.second = stoi(command->arguments[0]) - 1;
            shared_ptr<IWaitingCommand> move(new MoveCommand(world, selectedCoordination, pos));
            waitingCommands.addCommand(move);
            continue;
        }
        if (inputCommand == Command::WAIT) {
            waitingCommands.runCommands(world, stoi(command->arguments[0]));
            continue;
        }
        if (inputCommand == Command::BUILD) {
            shared_ptr <IWaitingCommand> build(new BuildCommand(command, world));
            waitingCommands.addCommand(build);
            continue;
        }
        if (inputCommand == Command::PEOPLE) {
            world->addPeople(command);
            continue;
        }
        if (inputCommand == Command::DEPOSIT) {
            world->deposit(command, selectedCoordination);
            continue;
        }
    }
}

void runAssertsCommands(shared_ptr<WorldMap> world, Input const& input, pair<int, int> selectedCoordination)
{
    for (string assertName : input.asserts) {
        shared_ptr<Command> assertCommand = input.parse_command(assertName);
        if (assertName == "SelectedCategory") {
            cout << assertName << " " << world->getCategory(selectedCoordination.first, selectedCoordination.second);
        }
        else if (assertName == "SelectedResource") {
            cout << assertName << " " << world->getResource(selectedCoordination.first, selectedCoordination.second);
        }
        else if (assertName == "CityCount") {
            cout << assertName << " " << City::count;
        }
        else if (assertName == "VillageCount") {
            cout << assertName << " " << Village::count;
        }
        else if (assertName == "RoadCount") {
            cout << assertName << " " << Road::count;
        }
        else if (assertName == "SelectedComplete") {
            cout << assertName << " false";
        }
        else if (assertName == "SelectedPeople") {
            cout << assertName << " " << world->getSelectedPeople(selectedCoordination);;
        }
        cout<<endl;
    }
}
