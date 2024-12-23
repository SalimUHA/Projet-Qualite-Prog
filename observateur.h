//
// Created by SAID on 20/12/2024.
//

#ifndef OBSERVATEUR_H
#define OBSERVATEUR_H
#include "Position.h"

class observateur {
public:
    virtual void miseAJour(const position& pos, const std::string& direction) = 0;
    virtual ~observateur() = default;
};


#endif //OBSERVATEUR_H
