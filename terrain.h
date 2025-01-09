#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "celulle.h"
#include "position.h"

class terrain {
public:
    terrain(int largeur = 0, int hauteur = 0);

    // Gestion des dimensions
    int obtenirLargeur() const;
    int obtenirHauteur() const;

    // Accès aux cellules
    cellule obtenirCellule(const position &pos) const;

     // Positions spéciales
    position obtenirPositionDepart() const;
    position obtenirPositionArrivee() const;

    // Modifications du terrain
    void definirMur(const position &pos);
    void definirDepart(const position &pos);
    void definirArrivee(const position &pos);

    // Affichage du terrain
    void afficherTerrain(int modeAffichage) const;
    void afficherTerrain(const position &robotPos, const std::string &robotDirection,int modeAffichage) const;

    // Sauvegarde et chargement
    void chargerDepuisFichier(const std::string &nomFichier);

    // Vérification des cellules
    bool estLibre(int x, int y) const;

    // Accès aux cases
    cellule getCase(int x, int y) const;

private:
    int d_largeur;
    int d_hauteur;
    std::vector<std::vector<cellule>> d_grille;
    position d_robotPos;

    void initialiserTerrain(int largeur, int hauteur);
};

#endif // TERRAIN_H
