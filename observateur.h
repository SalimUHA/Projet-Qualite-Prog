//
// Created by SAID on 20/12/2024.
//

#ifndef OBSERVATEUR_H
#define OBSERVATEUR_H
#include "Position.h"

class Observateur {
public:
    virtual void miseAJour(const Position& pos, const std::string& direction) = 0;
    virtual ~Observateur() = default;
};


#endif //OBSERVATEUR_H
