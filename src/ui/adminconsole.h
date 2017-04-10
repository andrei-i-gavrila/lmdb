//
// Created by Andrei Gavrila on 06.04.2017.
//

#ifndef LMDB_ADMINCONSOLE_H
#define LMDB_ADMINCONSOLE_H

#include <unordered_map>
#include "../controller/movie_controller.h"

class AdminConsole {
private:
    MovieController& mc;
    std::unordered_map<std::string, std::string> commandsDesc;
    std::unordered_map<std::string, std::function<void()>> commandsFunc;
    Vector<std::string> commandsOrder;
    bool running;
public:
//    AdminConsole();
    AdminConsole(MovieController& mc);
    
    AdminConsole(AdminConsole&& c);
    
    AdminConsole& operator =(AdminConsole& other);
    
    void run();

private:
    void initCommands();
    
    void add();
    
    void help();
    
    void show();
    
    void readCommand(std::string& cmd);
    
    void remove();
    
    void filterDuration();
};

#endif //LMDB_CONSOLE_H
