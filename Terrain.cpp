//
// Created by salim on 11/12/2024.
//

#include "Terrain.h"

Terrain::Terrain(int largeur, int hauteur):
 d_largeur(largeur), d_hauteur(hauteur)
{
  d_grille.resize(hauteur, std::vector<Cellule>(largeur,Cellule()));
}

int Terrain::obtenirLargeur() const
    {
    return d_largeur;
    }
int Terrain::obtenirHauteur() const
        {
  return d_hauteur;
  }

Cellule Terrain::obtenirCellule(const Position &pos) const
      {
          return d_grille[pos.y()][pos.x()];
      }

Position Terrain::obtenirPositionDepart() const
          {
  Position depart;
  int i = 0, j = 0;
  bool trouve = false;

  while (i < d_hauteur && !trouve) {
    j = 0;
    while (j < d_largeur && !trouve) {
      if (d_grille[i][j].estDepart()) {
        depart.deplaceEn(i, j);
        trouve = true;
      }
      j++;
    }
    i++;
  }

  return depart;
  }

Position Terrain::obtenirPositionArrivee() const
{
  Position arrivee;
  int i = 0, j = 0;
  bool trouve = false;

  while (i < d_hauteur && !trouve) {
    j = 0;
    while (j < d_largeur && !trouve) {
      if (d_grille[i][j].estArrivee()) {
        arrivee.deplaceEn(i, j);
        trouve = true;
      }
      j++;
    }
    i++;
  }

  return arrivee;
}

void Terrain::definirMur(const Position &pos)
    {
  d_grille[pos.y()][pos.x()].rendreMur();
  }

void Terrain::definirDepart(const Position &pos)
      {
  d_grille[pos.y()][pos.x()].rendreDepart();
  }

void Terrain::definirArrivee(const Position &pos)
      {
  d_grille[pos.y()][pos.x()].rendreArrivee();
  }

void Terrain::afficherTerrain() const
      {
    for (int i = 0; i < d_hauteur; ++i)
  {
      for (int j = 0; j < d_largeur; ++j)
      {
        d_grille[i][j].afficherCellule();
      }
      std::cout << std::endl;
    }
  }
