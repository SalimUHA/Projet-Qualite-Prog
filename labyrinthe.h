#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include "terrain.h"
#include "robot.h"
#include "observateurStatistiques.h"
#include <string>

class labyrinthe {
private:
    terrain d_terrain;
    robot* d_robot;
    observateurStatistiques* d_stats;
    int d_algorithmeChoisi;
    int d_modeAffichage; // Nouveau : mode d'affichage sélectionné
    bool terrainCharge;

public:
    labyrinthe();
    ~labyrinthe();

    void chargerTerrain(const std::string& nomFichier);
    void choisirAlgorithme(int algorithme);
    void choisirModeAffichage(int mode); // Nouveau : méthode pour choisir un mode d'affichage
    void lancerJeu();
    void afficherMenu();
};

#endif // LABYRINTHE_H
