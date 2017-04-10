//
// Created by Andrei Gavrila on 07.04.2017.
//

#include <iostream>
#include "userconsole.h"


UserConsole::UserConsole(MovieController& mc): mc(mc) {
    this->initCommands();
    
}

UserConsole::UserConsole(UserConsole&& c): mc(c.mc) {
//    this->mc = c.mc;
    this->commandsDesc = c.commandsDesc;
    this->commandsFunc = c.commandsFunc;
    this->commandsOrder = c.commandsOrder;
    this->initCommands();
    
}

void UserConsole::add() {
    if (!this->mc.selectionStarted()) {
        std::cout << "No selection\n";
        return;
    }
    
    this->mc.addToWatchlist();
    this->nextSelection();
}

void UserConsole::remove() {
    
    std::cout << "Give me a name and a year:\n";
    
    std::string name;
    int year;
    while (!(std::cin >> name >> year)) {
        std::cout << "Invalid input. Give me a name and a year (none can be empty):\n";
    }
    
    std::cout << "Did you like it?(y/n)";
    std::string like;
    std::cin >> like;
    if (this->mc.removeFromWatchlist(name, year, like)) {
        std::cout << "Removed successfully\n";
    } else {
        std::cout << "Not existent\n";
    }
}

void UserConsole::show() {
    if (this->mc.getWatchlist().size() == 0) {
        std::cout << "No watchlist\n";
        return;
    }
    
    for (const auto& mov: this->mc.getWatchlist()) {
        std::cout << mov.first << " (" << mov.second << ").\n";
    }
}

void UserConsole::initCommands() {
    
    this->commandsOrder.push_back("start");
    this->commandsDesc["start"] = "Start a selection";
    this->commandsFunc["start"] = std::function<void()>([this]() {this->startSelection();});
    
    this->commandsOrder.push_back("watcht");
    this->commandsDesc["watcht"] = "Watch the trailer";
    this->commandsFunc["watcht"] = std::function<void()>([this]() {this->watchTrailer();});
    
    this->commandsOrder.push_back("stop");
    this->commandsDesc["stop"] = "Stop a selection";
    this->commandsFunc["stop"] = std::function<void()>([this]() {this->stopSelection();});
    
    this->commandsOrder.push_back("next");
    this->commandsDesc["next"] = "Next movie from selection";
    this->commandsFunc["next"] = std::function<void()>([this]() {this->nextSelection();});
    
    this->commandsOrder.push_back("add");
    this->commandsDesc["add"] = "Add a movie to the watchlist";
    this->commandsFunc["add"] = std::function<void()>([this]() {this->add();});
    
    this->commandsOrder.push_back("show");
    this->commandsDesc["show"] = "Show the watchlist";
    this->commandsFunc["show"] = std::function<void()>([this]() {this->show();});
    
    this->commandsOrder.push_back("remove");
    this->commandsDesc["remove"] = "Remove a movie from the watchlist";
    this->commandsFunc["remove"] = std::function<void()>([this]() {this->remove();});
    
    this->commandsOrder.push_back("help");
    this->commandsDesc["help"] = "Show this menu";
    this->commandsFunc["help"] = std::function<void()>([this]() {this->help();});
    
    
    this->commandsFunc["invalid"] = std::function<void()>([this]() {std::cout << "Invalid\n";});
    this->commandsFunc["exit"] = std::function<void()>([this]() {
        this->running = false;
        this->stopSelection();
    });
    
}

void UserConsole::help() {
    for (const auto& cmd : this->commandsOrder) {
        std::cout << cmd << ": " << this->commandsDesc[cmd] << "\n";
    }
}


void UserConsole::readCommand(std::string& cmd) {
    std::cin >> cmd;
    if (!this->commandsFunc[cmd]) {
        cmd = "invalid";
    }
}

void UserConsole::run() {
    this->running = true;
    this->help();
    
    while (running) {
        
        if (this->mc.selectionStarted()) {
            std::cout << "Current movie: " << this->mc.getCurrentFromSelection() << "\n";
            std::cout << "Your options are: watch trailer, add, or next.\n";
        }
        
        std::string cmd;
        readCommand(cmd);
        commandsFunc[cmd]();
    }
}

UserConsole& UserConsole::operator =(UserConsole& other) {
//    this->mc = MovieController(other.mc);
    return *this;
}

void UserConsole::startSelection() {
    
    std::string query;
    
    std::cout << "Enter genre. Leave empty for all:\n";
    std::cin.get();
    std::getline(std::cin, query);
    
    this->mc.newSelection(query);
    
    if (this->mc.selectionStarted()) {
        this->nextSelection();
    } else {
        std::cout << "No matches\n";
    }
}

void UserConsole::watchTrailer() {
    if (!this->mc.selectionStarted()) {
        std::cout << "No selection\n";
        return;
    }
    
    this->mc.watchTrailer();
}

void UserConsole::stopSelection() {
    if (!this->mc.selectionStarted()) {
        std::cout << "No selection\n";
        return;
    }
    
    this->mc.stopSelection();
}

void UserConsole::nextSelection() {
    if (!this->mc.selectionStarted()) {
        std::cout << "No selection\n";
        return;
    }
    
    
    this->mc.nextMovie();
}


