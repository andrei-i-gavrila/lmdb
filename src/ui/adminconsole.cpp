//
// Created by Andrei Gavrila on 06.04.2017.
//

#include <iostream>
#include "adminconsole.h"


AdminConsole::AdminConsole(MovieController& m): mc(m) {
    this->initCommands();
    
}

AdminConsole::AdminConsole(AdminConsole&& c): mc(c.mc) {
//    this->mc = c.mc;
    this->commandsDesc = c.commandsDesc;
    this->commandsFunc = c.commandsFunc;
    this->commandsOrder = c.commandsOrder;
    this->initCommands();
    
}

void AdminConsole::add() {
    std::cout << "Give me a name, year, genre, trailer and duration (none can be empty):\n";
    std::string name, genre, trailer;
    int year, duration;
    while (!(std::cin >> name >> year >> genre >> trailer >> duration)) {
        std::cout << "Invalid input. Give me a name, year, genre, trailer and duration (none can be empty):\n";
    }
    
    if (this->mc.addMovie(name, year, genre, trailer, duration)) {
        std::cout << "Added successfully\n";
    } else {
        std::cout << "Updated existing movie\n";
    }
}

void AdminConsole::remove() {
    std::cout << "Give me a name and a year (none can be empty):\n";
    
    std::string name;
    int year;
    while (!(std::cin >> name >> year)) {
        std::cout << "Invalid input. Give me a name and a year (none can be empty):\n";
    }
    
    if (this->mc.removeMovie(name, year)) {
        std::cout << "Removed successfully\n";
    } else {
        std::cout << "Not existent\n";
    }
    
}

void AdminConsole::show() {
    for (const auto& mov: this->mc.getAll()) {
        std::cout << mov << "\n";
    }
}

void AdminConsole::initCommands() {
    this->commandsOrder.push_back("add");
    this->commandsDesc["add"] = "Add a movie";
    this->commandsFunc["add"] = std::function<void()>([this]() {this->add();});
    
    this->commandsOrder.push_back("show");
    this->commandsDesc["show"] = "Show all movies";
    this->commandsFunc["show"] = std::function<void()>([this]() {this->show();});
    
    this->commandsOrder.push_back("remove");
    this->commandsDesc["remove"] = "Remove a movie";
    this->commandsFunc["remove"] = std::function<void()>([this]() {this->remove();});
    
    this->commandsOrder.push_back("help");
    this->commandsDesc["help"] = "Show this menu";
    this->commandsFunc["help"] = std::function<void()>([this]() {this->help();});
    
    this->commandsOrder.push_back("duration");
    this->commandsDesc["duration"] = "Filter movies less than a given duration";
    this->commandsFunc["duration"] = std::function<void()>([this]() {this->filterDuration();});
    
    
    this->commandsFunc["invalid"] = std::function<void()>([this]() {std::cout << "Invalid\n";});
    this->commandsFunc["exit"] = std::function<void()>([this]() {this->running = false;});
    
}

void AdminConsole::help() {
    for (const auto& cmd : this->commandsOrder) {
        std::cout << cmd << ": " << this->commandsDesc[cmd] << "\n";
    }
}


void AdminConsole::readCommand(std::string& cmd) {
    std::cin >> cmd;
    if (!this->commandsFunc[cmd]) {
        cmd = "invalid";
    }
}

void AdminConsole::run() {
    this->running = true;
    this->help();
    
    while (running) {
        std::string cmd;
        readCommand(cmd);
        commandsFunc[cmd]();
    }
}

AdminConsole& AdminConsole::operator =(AdminConsole& other) {
//    this->mc = MovieController(other.mc);
    return *this;
}

void AdminConsole::filterDuration() {
    std::cout << "Give me a duration\n";
    int duration;
    while (!(std::cin >> duration)) {
        std::cout << "Invalid. Give me a duration\n";
        
    }
    auto fil = this->mc.durationLessthan(duration);
    
    if (fil->size() == 0) {
        std::cout << "No matches\n";
    }
    
    for (auto& t : *fil) {
        std::cout << t << "\n";
    }
    
    delete fil;
}
