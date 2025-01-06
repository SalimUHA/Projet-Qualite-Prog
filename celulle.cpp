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
char cellule::obtenirCaractere() const
{
        if (estMur())
    {
        return 'X'; // Mur
    }
    else if (estDepart())
    {
        return 'S'; // Départ
    }
    else if (estArrivee())
    {
        return 'E'; // Arrivée
    }
    else
    {
        return '.'; // Case vide
    }
}
void cellule::afficherCellule() const
{
        std::cout << obtenirCaractere();
}

cellule& cellule::operator=(const cellule& c2)
{
    if (this != &c2)
  {
        d_type = c2.d_type;
  }
    return *this;
}

void cellule::initialiserDepuisCaractere(char c)
{
    if (c == 'X')
    {
        rendreMur();
    }
    else if (c == 'S')
    {
        rendreDepart();
    }
    else if (c == 'E')
    {
        rendreArrivee();
    }
    else if (c == '.')
    {
        rendreVide();
    }
    else
    {
        std::cerr << "Caractere inconnu '" << c << "'. On le rend vide" << std::endl;
        rendreVide();
    }
}
