//
// Created by salim on 12/12/2024.
//

#ifndef CELULLE_H
#define CELULLE_H
#include <iostream>
#include <string>

class Cellule {

const int CELLULE_VIDE = 0;
const int CELLULE_MUR = 1;
const int CELLULE_DEPART = 2;
const int CELLULE_ARRIVEE = 3;

public:
  Cellule(int type);
  std::string ObtenirType() const;
  void RendreMur();
  void RendreVide();
  void RendreDepart();
  void RendreArrive();
  bool estMur() const;
  bool estVide() const;
  bool estDepart() const;
  bool estArrivee() const;
  void afficherCelulle() const;

private:
  int d_type;
};



#endif //CELULLE_H
