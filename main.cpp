//
// Created by salim on 12/12/2024.
//
#include <iostream>
#include "Terrain.h"
int main()
   {

    terrain terrain(5, 5);

    terrain.definirMur(position(0, 0));
    terrain.definirMur(position(1, 0));
    terrain.definirDepart(position(1, 1));
    terrain.definirArrivee(position(3, 3));

    terrain.afficherTerrain();

    std::cout<<"test";
    return 0;
  }
