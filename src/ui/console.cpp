//
// Created by Andrei Gavrila on 07.04.2017.
//

#include <iostream>
#include "console.h"

void Console::run() {
    std::string cmd;
    
    while (true) {
        std::cout << "Choose user or admin!\n";
        
        std::cin >> cmd;
        
        
        if (cmd == "admin") {
            ac.run();
        } else if (cmd == "user") {
            uc.run();
        } else if (cmd == "exit") {
            break;
        } else {
            std::cout << "Invalid. ";
        }
    }
}

Console::Console(MovieController& m): ac(AdminConsole(m)), uc(UserConsole(m)) {
}
