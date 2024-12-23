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
  Cellule();
  int  obtenirType() const;
  void rendreMur();
  void rendreVide();
  void rendreDepart();
  void rendreArrivee();
  bool estMur() const;
  bool estVide() const;
  bool estDepart() const;
  bool estArrivee() const;
  void afficherCellule() const;
  Cellule& operator=(const Cellule &c2);

private:
  int d_type;
};



#endif //CELULLE_H
