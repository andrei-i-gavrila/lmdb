//
// Created by Andrei Gavrila on 07.04.2017.
//

#ifndef LMDB_USERCONSOLE_H
#define LMDB_USERCONSOLE_H

#include <unordered_map>
#include "../controller/movie_controller.h"

class UserConsole {
private:
    MovieController& mc;
    std::unordered_map<std::string, std::string> commandsDesc;
    std::unordered_map<std::string, std::function<void()>> commandsFunc;
    Vector<std::string> commandsOrder;
    bool running;
public:
//    UserConsole();
    UserConsole(MovieController& mc);
    
    UserConsole(UserConsole&& c);
    
    UserConsole& operator =(UserConsole& other);
    
    void run();

private:
    void initCommands();
    
    void add();
    
    void help();
    
    void show();
    
    void readCommand(std::string& cmd);
    
    void remove();
    
    void startSelection();
    
    void watchTrailer();
    
    void stopSelection();
    
    void nextSelection();
};


#endif //LMDB_USERCONSOLE_H
