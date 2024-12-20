//faut verifier
#include "Robot.h"
#include "Terrain.h"

Robot::Robot(const Position& startPos)
    : d_position(startPos), d_direction("NORD") {}

void Robot::ajouterObservateur(Observateur* obs) {
    d_observateurs.push_back(obs);
}

void Robot::supprimerObservateur(Observateur* obs) {
    d_observateurs.erase(
        std::remove(d_observateurs.begin(), d_observateurs.end(), obs),
        d_observateurs.end()
    );
}

void Robot::notifierObservateurs() {
    for (auto* obs : d_observateurs) {
        obs->miseAJour(d_position, d_direction);
    }
}

void Robot::avancerUneCase() {
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

void Robot::tournerDroite() {
    if (d_direction == "NORD") d_direction = "EST";
    else if (d_direction == "EST") d_direction = "SUD";
    else if (d_direction == "SUD") d_direction = "OUEST";
    else if (d_direction == "OUEST") d_direction = "NORD";

    notifierObservateurs();
}

void Robot::tournerGauche() {
    if (d_direction == "NORD") d_direction = "OUEST";
    else if (d_direction == "OUEST") d_direction = "SUD";
    else if (d_direction == "SUD") d_direction = "EST";
    else if (d_direction == "EST") d_direction = "NORD";

    notifierObservateurs();
}


bool Robot::detecterObstacle(const Terrain& terrain) const {
    Position prochainePosition = d_position;


    if (d_direction == "NORD") {
        prochainePosition.deplaceDe(0, -1);
    } else if (d_direction == "EST") {
        prochainePosition.deplaceDe(1, 0);
    } else if (d_direction == "SUD") {
        prochainePosition.deplaceDe(0, 1);
    } else if (d_direction == "OUEST") {
        prochainePosition.deplaceDe(-1, 0);
    }


    if (terrain.obtenirCelulle(prochainePosition).estMur()) {
        return true;
    }
    return false;
}