//
// Created by salim on 12/12/2024.
//
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h> // Pour les caractères unicode
#include "labyrinthe.h"


int main()
{
    labyrinthe jeu;
    SetConsoleOutputCP(65001);
    jeu.afficherMenu();
    return 0;
}




