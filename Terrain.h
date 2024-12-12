//
// Created by salim on 11/12/2024.
//

#ifndef TERRAIN_H
#define TERRAIN_H
#include <iostream>
#include <vector>
#include "Position.h"
#include "Celulle.h"

class Terrain {
public:
  Terrain(int largeur, int hauteur); // Constructeur
  int obtenirLargeur() const;
  int obtenirHauteur() const;
  Cellule obtenirCelulle(const Position &pos) const;
  Position obtenirPositionDepart() const;
  Position obtenirPositionArrivee() const;
  void definirMur(const Position& pos);
  void definirDepart(const Position& pos);
  void definirArrivee(const Position& pos);
  void chargerDepuisFichier(const std::string &nomFichier);
  void sauvegarderDansFichier(const std::string &nomFichier) const;
  void AfficherTerrain() const;
private:
  int d_largeur, d_hauteur;
  std::vector<std::vector<Cellule>> d_grille;
  Position d_depart;
  Position d_arrive;
  Position d_robotPos;

};



#endif //TERRAIN_H
