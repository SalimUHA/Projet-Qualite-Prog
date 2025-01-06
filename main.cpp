//
// Created by salim on 12/12/2024.
//
#include <iostream>
#include "Terrain.h"
#include "robot.h"
#include "observateurConsole.h"

void testTerrain(){
    terrain terrain(5, 5);

    terrain.definirMur(position(0, 0));
    terrain.definirMur(position(1, 0));
    terrain.definirDepart(position(1, 1));
    terrain.definirArrivee(position(3, 3));

    terrain.afficherTerrain();
}

void testRobot()
{
    terrain terrain(5, 5);

    terrain.definirMur(position(0, 0));
    terrain.definirMur(position(1, 0));
    terrain.definirDepart(position(1, 1));
    terrain.definirArrivee(position(3, 3));

    terrain.afficherTerrain();
    robot robot(position(0,0));

    observateurConsole observateurConsole;
    robot.ajouterObservateur(&observateurConsole);


    std::cout << "\nDéplacement du robot :" << std::endl;

    robot.avancerUneCase();
    robot.tournerDroite();
    robot.avancerUneCase();
    robot.tournerDroite();
    robot.avancerUneCase();


    if (robot.detecterObstacle(terrain)) {
        std::cout << "Obstacle détecté ! Le robot ne peut pas avancer." << std::endl;
    } else {
        robot.avancerUneCase();
    }
}

void testSaveTerrain()
{
    terrain terrain(5, 5);

    // Configuration du terrain
    terrain.definirMur(position(0, 0));
    terrain.definirMur(position(1, 0));
    terrain.definirDepart(position(1, 1));
    terrain.definirArrivee(position(3, 3));

    terrain.sauvegarderDansFichier("terrain.txt");

    terrain.afficherTerrain();

    std::cout << "Terrain sauvegarde dans le fichier 'terrain.txt'." << std::endl;
}

void testerChargementDepuisFichier()
{
    std::string nomFichier = "terraintest.txt";

    terrain terrain(0, 0);

    terrain.chargerDepuisFichier(nomFichier);

    std::cout << "Terrain depuis le fichier '" << nomFichier << "' :\n";

    terrain.afficherTerrain();
}
int main()
{
    //testRobot();
    //testSaveTerrain();
    testerChargementDepuisFichier();
    return 0;
}




