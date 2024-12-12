//
// Created by salim on 12/12/2024.
//

#include "Celulle.h"

Cellule::Cellule(): d_type{"vide"}
{
}

Cellule::Cellule(const std::string &type): d_type{type}
{}

std::string Cellule::ObtenirType() const
   {
  return d_type;
  }

void Cellule::RendreMur()
  {
  d_type="mur";
  }

void Cellule::RendreVide()
      {
  d_type="vide";
  }

void Cellule::RendreDepart()
      {
  d_type="depart";
  }

void Cellule::RendreArrive()
      {
  d_type="arrive";
  }

bool Cellule::estMur() const{
  return d_type=="mur";
  }

bool Cellule::estVide() const{
    return d_type=="vide";
  }

bool Cellule::estDepart() const{
    return d_type=="depart";
  }
bool Cellule::estArrivee() const{
    return d_type=="arrive";
  }