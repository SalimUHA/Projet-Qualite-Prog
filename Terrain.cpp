//
// Created by salim on 11/12/2024.
//

#include "terrain.h"

terrain::Terrain(int largeur, int hauteur):
 d_largeur(largeur), d_hauteur(hauteur)
{
  d_grille.resize(hauteur, std::vector<Cellule>(largeur,Cellule()));
}

int terrain::obtenirLargeur() const
    {
    return d_largeur;
    }
int terrain::obtenirHauteur() const
        {
  return d_hauteur;
  }

Cellule terrain::obtenirCellule(const position &pos) const
      {
          return d_grille[pos.y()][pos.x()];
      }

position terrain::obtenirPositionDepart() const
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

Position terrain::obtenirPositionArrivee() const
{
  position arrivee;
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

void terrain::definirMur(const Position &pos)
    {
  d_grille[pos.y()][pos.x()].rendreMur();
  }

void terrain::definirDepart(const Position &pos)
      {
  d_grille[pos.y()][pos.x()].rendreDepart();
  }

void terrain::definirArrivee(const Position &pos)
      {
  d_grille[pos.y()][pos.x()].rendreArrivee();
  }

void terrain::afficherTerrain() const
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
