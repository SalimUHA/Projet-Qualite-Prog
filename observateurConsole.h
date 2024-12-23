//
// Created by SAID on 20/12/2024.
//



#ifndef OBSERVATEUR_CONSOLE_H
#define OBSERVATEUR_CONSOLE_H

#include "observateur.h"
#include <iostream>

class observateurConsole : public observateur {
public:
    void miseAJour(const Position& pos, const std::string& direction) override ;
};
#endif //OBSERVATEURCONSOLE_H
