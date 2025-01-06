//
// Created by said on 11/12/2024.
//

#ifndef TERRAIN_H
#define TERRAIN_H
#include <iostream>
#include <vector>
#include <fstream>
#include "position.h"
#include "celulle.h"

class terrain {
public:
  terrain(int largeur, int hauteur); // Constructeur
  void initialiserTerrain(int largeur, int hauteur);
  int obtenirLargeur() const;
  int obtenirHauteur() const;
  cellule obtenirCellule(const position &pos) const;
  position obtenirPositionDepart() const;
  position obtenirPositionArrivee() const;
  void definirMur(const position& pos);
  void definirDepart(const position& pos);
  void definirArrivee(const position& pos);
  void chargerDepuisFichier(const std::string &nomFichier);
  void sauvegarderDansFichier(const std::string &nomFichier) const;
  //void afficherTerrain() const;
  void afficherTerrain(const position& robotPos) const;
private:
  int d_largeur, d_hauteur;
  std::vector<std::vector<cellule>> d_grille;
  position d_depart;
  position d_arrive;
  position d_robotPos;

};



#endif //TERRAIN_H
