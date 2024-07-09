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
//#include "WorldMap.h"
using namespace std;



void runStartCommands(WorldMap& world, Input const& input);
void runAssertsCommands(WorldMap const& world, Input const& input, pair<int, int> selectedCoordination);
void runInputCommands(WorldMap & world, Input const& input);

Position selectedCoordination;
WaitingCommands waitingCommands;

int main()
{
    Input input;
    input.parse_and_store();

    WorldMap world(input);//WorldMap constructor fills the world grid


    runStartCommands(world, input);
    runInputCommands(world, input); 
    runAssertsCommands(world, input, selectedCoordination);
    return 0;
}

void runStartCommands(WorldMap & world, Input const& input)
{
    for(shared_ptr<Command> command: input.start){
        string startCommand = command->name;
        if (startCommand == Command::RESOURCE){
            //TODO: try catch
            world.startResource(input);
            continue;
        }
        if (startCommand == Command::PEOPLE){
            //TODO: try catch
            world.startPeople(input);
            continue;
        }
        if (startCommand == Command::BUILD) {
            world.startbuild(*command.get());
            continue;
        }
    }
}
//
/////////////////////////////////////////////////////////////////////////////
void runInputCommands(WorldMap & world, Input const& input)
{

    for (shared_ptr< Command> command : input.steps) {
        string inputCommand = command->name;
        if (inputCommand == Command::SELECT)
        {
            int y = stoi(command->arguments[0]) - 1, x = stoi(command->arguments[1]) - 1;
            selectedCoordination.first = x;
            selectedCoordination.second = y;
        }
        if (inputCommand == Command::RAIN)
        {
            shared_ptr <IWaitingCommand> rain(new RainCommand(stoi(command->arguments[0]), world));
            waitingCommands.addCommand(rain);
        }
        if(inputCommand == Command::WORK)
        {
            if (Person* p = dynamic_cast<Person*>(world.getCoordination(selectedCoordination).entity.get())){
                Position pos;
                pos.first = stoi(command->arguments[1]) - 1;
                pos.second = stoi(command->arguments[0]) - 1;
           //     MoveCommand::FunctionPtr ptr = &Person::work;
                shared_ptr<IWaitingCommand> move(new MoveCommand(world, selectedCoordination, pos));
                waitingCommands.addCommand(move);
            }

        }
        if (inputCommand == Command::MOVE) {
            Position pos;
            pos.first = stoi(command->arguments[1]) - 1;
            pos.second = stoi(command->arguments[0]) - 1;
            shared_ptr<IWaitingCommand> move(new MoveCommand(world, selectedCoordination, pos));
            waitingCommands.addCommand(move);
        }
        if (inputCommand == Command::WAIT)
            waitingCommands.runCommands(world, stoi(command->arguments[0]));
        
        if (inputCommand == Command::BUILD) {
            shared_ptr <IWaitingCommand> build(new BuildCommand(command));
            waitingCommands.addCommand(build);
        }
    }
}

void runAssertsCommands(WorldMap const& world, Input const& input, pair<int, int> selectedCoordination)
{
    shared_ptr<Command> assertCommand = input.parse_command(input.asserts[0]);
    string firstAssert, result="";
    firstAssert = assertCommand.get()->name;
    if (firstAssert == "SelectedCategory") {
        cout << firstAssert << " " << world.getCategory(selectedCoordination.first, selectedCoordination.second);
        return;
    }
    if (firstAssert == "SelectedResource") {
        cout << firstAssert << " " << world.getResource(selectedCoordination.first, selectedCoordination.second);
        return;
    }
}
