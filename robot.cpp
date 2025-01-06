
#include "robot.h"
#include "Terrain.h"
#include <algorithm>


robot::robot(const position& startPos)
    : d_position(startPos), d_direction("NORD") {}

position robot::obtenirPosition() const {
    return d_position;
}

void robot::deplacer(const position& nouvellePos){
    d_position.deplaceEn(nouvellePos.x(),nouvellePos.y());
}
void robot::ajouterObservateur(observateur* obs) {
    d_observateurs.push_back(obs);
}



void robot::supprimerObservateur(observateur* obs) {
    auto it = std::remove(d_observateurs.begin(), d_observateurs.end(), obs);
    if (it != d_observateurs.end()) {
        d_observateurs.erase(it, d_observateurs.end());
    }
}


void robot::notifierObservateurs()
{
    for (auto* obs : d_observateurs)
        {
        obs->miseAJour(d_position, d_direction);
        }
}

void robot::avancerUneCase() {
    if (d_direction == "NORD") {
        d_position.deplaceDe(0, -1);
    } else if (d_direction == "EST") {
        d_position.deplaceDe(1, 0);
    } else if (d_direction == "SUD") {
        d_position.deplaceDe(0, 1);
    } else if (d_direction == "OUEST") {
        d_position.deplaceDe(-1, 0);
    }

    notifierObservateurs();
}

void robot::tournerDroite() {
    if (d_direction == "NORD") d_direction = "EST";
    else if (d_direction == "EST") d_direction = "SUD";
    else if (d_direction == "SUD") d_direction = "OUEST";
    else if (d_direction == "OUEST") d_direction = "NORD";

    notifierObservateurs();
}

void robot::tournerGauche() {
    if (d_direction == "NORD") d_direction = "OUEST";
    else if (d_direction == "OUEST") d_direction = "SUD";
    else if (d_direction == "SUD") d_direction = "EST";
    else if (d_direction == "EST") d_direction = "NORD";

    notifierObservateurs();
}


bool robot::detecterObstacle(const terrain& terrain) const {
    position prochainePosition = d_position;


    if (d_direction == "NORD") {
        prochainePosition.deplaceDe(0, -1);
    } else if (d_direction == "EST") {
        prochainePosition.deplaceDe(1, 0);
    } else if (d_direction == "SUD") {
        prochainePosition.deplaceDe(0, 1);
    } else if (d_direction == "OUEST") {
        prochainePosition.deplaceDe(-1, 0);
    }


    if (terrain.obtenirCellule(prochainePosition).estMur()) {
        return true;
    }
    return false;
}
