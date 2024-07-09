#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Command.h"
#include "Utility.h"

class Input
{

    void start_lines();
    std::string next_line();
public:
    Input()
    {
        world.reset(new Command(Command::WORLD));
    }
    void parse_and_store();

    std::shared_ptr<Command> world;
    std::vector< std::shared_ptr<Command> > start;
    std::vector< std::shared_ptr<Command> > steps;

    std::vector<std::string> asserts;

    static std::shared_ptr<Command> parse_command(std::string line);
};

