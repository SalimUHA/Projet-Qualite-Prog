#include "labyrinthe.h"
#include <iostream>
#include <fstream>

labyrinthe::labyrinthe()
    : d_terrain(0, 0), d_robot(nullptr), d_algorithmeChoisi(0), terrainCharge(false), d_stats(nullptr) {}

labyrinthe::~labyrinthe() {
    if (d_robot) {
        delete d_robot;
    }
    if (d_stats) {
        delete d_stats;
    }
}

void labyrinthe::chargerTerrain(const std::string& nomFichier) {
    if (d_robot) {
        delete d_robot;
        d_robot = nullptr;
    }
    if (d_stats) {
        delete d_stats;
        d_stats = nullptr;
    }

    std::ifstream fichier(nomFichier);
    if (!fichier) {
        std::cout << "Erreur : Impossible d'ouvrir le fichier " << nomFichier << ".\n";
        terrainCharge = false;
        return;
    }

    d_terrain.chargerDepuisFichier(nomFichier);
    position depart = d_terrain.obtenirPositionDepart();
    d_robot = new robot(depart);
    d_stats = new observateurStatistiques(depart);
    d_robot->ajouterObservateur(d_stats);
    terrainCharge = true;

    std::cout << "Terrain chargé avec succès :\n";
    d_terrain.afficherTerrain();
}

void labyrinthe::choisirAlgorithme(int algorithme) {
    if (!terrainCharge) {
        std::cout << "Erreur : Aucun terrain valide chargé.\n";
        return;
    }

    if (algorithme == 1 || algorithme == 2) {
        d_algorithmeChoisi = algorithme;
        std::cout << "Algorithme choisi : "
                  << (algorithme == 1 ? "Main Droite" : "Pledge")
                  << std::endl;
    } else {
        std::cout << "Erreur : Algorithme invalide.\n";
    }
}

void labyrinthe::lancerJeu() {
    if (!terrainCharge) {
        std::cout << "Erreur : Aucun terrain valide chargé.\n";
        return;
    }

    if (d_algorithmeChoisi == 0) {
        std::cout << "Erreur : Aucun algorithme choisi.\n";
        return;
    }

    if (!d_robot) {
        std::cout << "Erreur : Robot non initialisé.\n";
        return;
    }

    delete d_robot;
    d_robot = new robot(d_terrain.obtenirPositionDepart());
    d_robot->ajouterObservateur(d_stats);

    if (d_algorithmeChoisi == 1) {
        d_robot->appliquerMainDroite(d_terrain);
    } else if (d_algorithmeChoisi == 2) {
        d_robot->appliquerPledge(d_terrain);
    }

    if (d_stats) {
        std::cout << "Nombre total de cases parcourues : "
                  << d_stats->obtenirNombreCasesParcourues() << std::endl;
    }

    std::cout << "Jeu terminé.\n";
}

void labyrinthe::afficherMenu() {
    int choix = 0;
    while (choix != 4) {
        std::cout << "=== Menu Labyrinthe ===\n";
        std::cout << "1. Charger un terrain\n";
        std::cout << "2. Choisir un algorithme\n";
        std::cout << "3. Lancer le jeu\n";
        std::cout << "4. Quitter\n";
        std::cout << "Votre choix : ";
        std::cin >> choix;

        switch (choix) {
            case 1: {
                std::string nomFichier;
                std::cout << "Entrez le nom du fichier : ";
                std::cin >> nomFichier;
                chargerTerrain(nomFichier);
                break;
            }
            case 2: {
                if (!terrainCharge) {
                    std::cout << "Erreur : Veuillez charger un terrain avant de choisir un algorithme.\n";
                } else {
                    int algorithme;
                    std::cout << "1. Main Droite\n";
                    std::cout << "2. Pledge\n";
                    std::cout << "Votre choix : ";
                    std::cin >> algorithme;
                    choisirAlgorithme(algorithme);
                }
                break;
            }
            case 3: {
                lancerJeu();
                break;
            }
            case 4: {
                std::cout << "Au revoir !\n";
                exit(0);
            }
            default:
                std::cout << "Erreur : Option invalide.\n";
        }
    }
}
