#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include "terrain.h"
#include "robot.h"
#include "observateurStatistiques.h"

class labyrinthe {
private:
    terrain d_terrain;
    robot* d_robot;
    int d_algorithmeChoisi;
    bool terrainCharge;
    observateurStatistiques* d_stats;

public:
    labyrinthe();
    ~labyrinthe();
    void chargerTerrain(const std::string& nomFichier);
    void choisirAlgorithme(int algorithme);
    void lancerJeu();
    void afficherMenu();
};

#endif // LABYRINTHE_H
