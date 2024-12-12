//
// Created by salim on 12/12/2024.
//

#ifndef CELULLE_H
#define CELULLE_H
#include <iostream>
#include <string>

class Cellule {
public:
  Cellule();
  Cellule(const std::string &type);
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
    std::string d_type;
};



#endif //CELULLE_H
