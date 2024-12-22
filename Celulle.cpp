//
// Created by salim on 12/12/2024.
//

#include "Celulle.h"

Cellule::Cellule(int type): d_type{type}
{}

int Cellule::ObtenirType() const
{
  return d_type;
}

void Cellule::RendreMur()
{
  d_type = CELLULE_MUR;
}

void Cellule::RendreVide()
{
  d_type = CELLULE_VIDE;
}

void Cellule::RendreDepart()
{
  d_type = CELLULE_DEPART;
}

void Cellule::RendreArrive()
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
