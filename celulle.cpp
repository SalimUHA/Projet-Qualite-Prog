#include "celulle.h"
using namespace std;

cellule::cellule(int type): d_type{type} {}

cellule::cellule(): d_type{CELLULE_VIDE} {}

int cellule::obtenirType() const {
  return d_type;
}

void cellule::rendreMur() {
  d_type = CELLULE_MUR;
}

void cellule::rendreVide() {
    if(d_type != CELLULE_MUR)
        d_type = CELLULE_VIDE;
}

void cellule::rendreDepart() {
  d_type = CELLULE_DEPART;
}

void cellule::rendreArrivee() {
  d_type = CELLULE_ARRIVEE;
}

void cellule::rendreRobot() {
    d_type = CELLULE_ROBOT;
}

bool cellule::estMur() const {
    return d_type == CELLULE_MUR;
}

bool cellule::estVide() const {
    return d_type == CELLULE_VIDE;
}

bool cellule::estDepart() const {
    return d_type == CELLULE_DEPART;
}

bool cellule::estArrivee() const {
    return d_type == CELLULE_ARRIVEE;
}

bool cellule::estRobot() const {
    return d_type == CELLULE_ROBOT;
}

char cellule::obtenirCaractere(int modeAffichage) const {
    if (modeAffichage == 1) {
        if (estMur()) {
            return 'X';
        } else if (estDepart()) {
            return 'E';
        } else if (estArrivee()) {
            return 'S';
        } else if (estRobot()) {
            return 'R';
        } else {
            return '.';
        }
    } else if (modeAffichage == 2) {
        if (estMur()) {
            return '|';
        } else if (estDepart()) {
            return '#';
        } else if (estArrivee()) {
            return '#';
        } else if (estRobot()) {
            return 'R';
        } else {
            return '.';
        }
    } else if (modeAffichage == 3) {
        if (estMur()) {
            return '\u2588';
        } else if (estDepart()) {
            return '\u25B2';
        } else if (estArrivee()) {
            return '\u25A0';
        } else if (estRobot()) {
            return '\u25CF';
        } else {
            return '\u25CB';
        }
    }
    return '?';
}

void cellule::afficherCellule(int modeAffichage) const {
    std::cout << obtenirCaractere(modeAffichage);
}

cellule& cellule::operator=(const cellule& c2) {
    if (this != &c2) {
        d_type = c2.d_type;
    }
    return *this;
}

void cellule::initialiserDepuisCaractere(char c) {
    if (c == 'X') {
        rendreMur();
    } else if (c == 'E') {
        rendreDepart();
    } else if (c == 'S') {
        rendreArrivee();
    } else if (c == 'R') {
        rendreRobot();
    } else if (c == '.') {
        rendreVide();
    } else {
        std::cerr << "Caractere inconnu '" << c << "'. On le rend vide" << std::endl;
        rendreVide();
    }
}
