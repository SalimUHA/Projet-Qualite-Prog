//
// Created by salim on 12/12/2024.
//

#ifndef CELULLE_H
#define CELULLE_H
#include <iostream>
#include <string>

class cellule {

static constexpr int CELLULE_VIDE = 0;
static constexpr int CELLULE_MUR = 1;
static constexpr int CELLULE_DEPART = 2;
static constexpr int CELLULE_ARRIVEE = 3;

public:
  cellule(int type);
  cellule();
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
  cellule& operator=(const cellule &c2);

private:
  int d_type;
};



#endif //CELULLE_H
