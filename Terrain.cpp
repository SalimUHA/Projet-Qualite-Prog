//
// Created by salim on 11/12/2024.
//

#include "Terrain.h"

Terrain::Terrain(int largeur, int hauteur):
 d_largeur(largeur), d_hauteur(hauteur)
{
  d_grille.resize(hauteur, std::vector<Cellule>(largeur));
}

int Terrain::obtenirLargeur() const
    {
    return d_largeur;
    }
int Terrain::obtenirHauteur() const
        {
  return d_hauteur;
  }
