//
// Created by salim on 12/12/2024.
//

#ifndef CELULLE_H
#define CELULLE_H
#include <iostream>
#include <string>
    static constexpr int CELLULE_VIDE = 0;
    static constexpr int CELLULE_MUR = 1;
    static constexpr int CELLULE_DEPART = 2;
    static constexpr int CELLULE_ARRIVEE = 3;
    static constexpr int CELLULE_ROBOT = 4;
class cellule {

public:
    cellule(int type);
    cellule();
    int  obtenirType() const;
    void rendreMur();
    void rendreVide();
    void rendreDepart();
    void rendreArrivee();
    void rendreRobot();
    bool estMur() const;
    bool estVide() const;
    bool estDepart() const;
    bool estArrivee() const;
    bool estRobot() const;
    void initialiserDepuisCaractere(char c);
    char obtenirCaractere(int modeAffichage) const;
    void afficherCellule(int modeAffichage) const;
    cellule& operator=(const cellule &c2);

private:
  int d_type;
};



#endif //CELULLE_H
