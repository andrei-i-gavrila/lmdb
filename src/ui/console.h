//
// Created by Andrei Gavrila on 07.04.2017.
//

#ifndef LMDB_CONSOLE_H
#define LMDB_CONSOLE_H

#include "adminconsole.h"
#include "userconsole.h"

class Console {
private:
    AdminConsole ac;
    UserConsole uc;

public:
    Console(MovieController& m);
    
    void run();
};

#endif //LMDB_CONSOLE_H
