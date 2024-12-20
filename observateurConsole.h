//
// Created by SAID on 20/12/2024.
//



#ifndef OBSERVATEUR_CONSOLE_H
#define OBSERVATEUR_CONSOLE_H

#include "Observateur.h"
#include <iostream>

class ObservateurConsole : public Observateur {
public:
    void miseAJour(const Position& pos, const std::string& direction) override ;

#endif //OBSERVATEURCONSOLE_H
