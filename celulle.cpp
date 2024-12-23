//
// Created by salim on 12/12/2024.
//

#include "celulle.h"
using namespace std;

cellule::cellule(int type): d_type{type}
{}

cellule::cellule(): d_type{CELLULE_VIDE}
{}

int cellule::obtenirType() const
{
  return d_type;
}

void cellule::rendreMur()
{
  d_type = CELLULE_MUR;
}

void cellule::rendreVide()
{
  d_type = CELLULE_VIDE;
}

void cellule::rendreDepart()
{
  d_type = CELLULE_DEPART;
}

void cellule::rendreArrivee()
{
  d_type = CELLULE_ARRIVEE;
}

bool cellule::estMur() const{
  return d_type == CELLULE_MUR;
}

bool cellule::estVide() const{
    return d_type == CELLULE_VIDE;
}

bool cellule::estDepart() const{
    return d_type == CELLULE_DEPART;
}
bool cellule::estArrivee() const{
    return d_type == CELLULE_ARRIVEE;
}

void cellule::afficherCellule() const
  {
            if (estMur())
                std::cout << "X";
            else if (estDepart())
                std::cout << "S";
            else if (estArrivee())
                std::cout << "E";
            else
                std::cout << ".";
}

cellule& cellule::operator=(const cellule& c2)
{
    if (this != &c2)
  {
        d_type = c2.d_type;
  }
    return *this;
}
