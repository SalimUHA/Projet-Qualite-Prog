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



int main()
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
    return 0;
}




