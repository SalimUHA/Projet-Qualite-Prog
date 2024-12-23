//
// Created by salim on 12/12/2024.
//

#include "Celulle.h"
using namespace std;

Cellule::Cellule(int type): d_type{type}
{}

Cellule::Cellule(): d_type{CELLULE_VIDE}
{}

int Cellule::obtenirType() const
{
  return d_type;
}

void Cellule::rendreMur()
{
  d_type = CELLULE_MUR;
}

void Cellule::rendreVide()
{
  d_type = CELLULE_VIDE;
}

void Cellule::rendreDepart()
{
  d_type = CELLULE_DEPART;
}

void Cellule::rendreArrivee()
{
  d_type = CELLULE_ARRIVEE;
}

bool Cellule::estMur() const{
  return d_type == CELLULE_MUR;
}

bool Cellule::estVide() const{
    return d_type == CELLULE_VIDE;
}

bool Cellule::estDepart() const{
    return d_type == CELLULE_DEPART;
}
bool Cellule::estArrivee() const{
    return d_type == CELLULE_ARRIVEE;
}

void Cellule::afficherCellule() const
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

Cellule& Cellule::operator=(const Cellule& c2)
{
    if (this != &c2)
  {
        d_type = c2.d_type;
  }
    return *this;
}
