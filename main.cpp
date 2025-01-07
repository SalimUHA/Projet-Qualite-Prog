//
// Created by salim on 12/12/2024.
//
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h> // Pour les caractères unicode
#include "terrain.h"
#include "robot.h"

void afficherMenu() {
    std::cout << "=== Sortie de labyrinthe ===" << std::endl;
    std::cout << "1. Lire un terrain depuis un fichier" << std::endl;
    std::cout << "2. Choisir un algorithme de sortie" << std::endl;
    std::cout << "3. Choisir un mode d'affichage" << std::endl;
    std::cout << "4. Faire sortir le robot" << std::endl;
    std::cout << "5. Quitter" << std::endl;
}

int main() {
    SetConsoleOutputCP(65001); // Permet l'affichage des caractères unicode
    terrain t{0, 0};

    int choix = 0;
    std::string nomFichier;
    int algorithmeChoisi = 0;
    int modeAffichage = 1;

    while (choix != 5) {
        afficherMenu();
        std::cout << "Choisissez une option : ";
        std::cin >> choix;

        switch (choix) {
            case 1: {
                std::cout << "Entrez le nom du fichier terrain : ";
                std::cin >> nomFichier;
                t.chargerDepuisFichier(nomFichier);
                t.afficherTerrain(); // Affichage initial du terrain

                break;
            }
            case 2: {
                std::cout << "Choisissez l'algorithme :\n";
                std::cout << "1. Main Droite\n";
                std::cout << "2. Pledge\n";
                std::cin >> algorithmeChoisi;
                break;
            }
            case 3: {
                std::cout << "Choisissez le mode d'affichage :\n";
                std::cout << "1. Mode texte simple\n";
                std::cout << "2. Mode texte amélioré 1\n";
                std::cout << "3. Mode texte amélioré 2\n";
                std::cin >> modeAffichage;
                break;
            }
            case 4: {
                // Configure l'affichage selon le mode choisi
                /*if (modeAffichage == 1) {
                    t.setModeAffichageSimple();
                } else if (modeAffichage == 2) {
                    t.setModeAffichageAmeliore1();
                } else if (modeAffichage == 3) {
                    t.setModeAffichageAmeliore2();
                }
                */
                // Exécution de l'algorithme choisi
                if (algorithmeChoisi == 1) {
                    position depart = t.obtenirPositionDepart();
                    robot r{depart};
                    r.appliquerMainDroite(t);
                } else if (algorithmeChoisi == 2) {
                    position depart = t.obtenirPositionDepart();
                    robot r{depart};
                    r.appliquerPledge(t);
                } else {
                    std::cout << "Algorithme non choisi ou invalide !\n";
                }

                // Affiche le nombre de cases parcourues
                //std::cout << "Nombre de cases parcourues : " << r.getNombreCasesParcourues() << std::endl;
                break;
            }
            case 5:
                std::cout << "Au revoir !" << std::endl;
                break;
            default:
                std::cout << "Option invalide !" << std::endl;
        }
    }

    return 0;
}




