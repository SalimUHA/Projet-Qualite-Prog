//
// Created by SAID on 20/12/2024.
//

#include "observateurConsole.h"
#include <iostream>

void ObservateurConsole::miseAJour(const Position& pos, const std::string& direction) {
    std::cout << "Position : " << pos << " | Direction : " << direction << std::endl;
}
