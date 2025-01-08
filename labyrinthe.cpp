#include "labyrinthe.h"
#include <iostream>
#include <fstream>

labyrinthe::labyrinthe()
    : d_terrain(0, 0), d_robot(nullptr), d_algorithmeChoisi(0), terrainCharge(false), d_stats(nullptr), d_modeAffichage(1) {}

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
    d_terrain.afficherTerrain(d_terrain.obtenirPositionDepart(), "NORD", d_modeAffichage);
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

void labyrinthe::choisirModeAffichage(int modeAffichage) {
    if (modeAffichage >= 1 && modeAffichage <= 3) {
        d_modeAffichage = modeAffichage;
        std::cout << "Mode d'affichage choisi : "
                  << (modeAffichage == 1 ? "Mode texte simple" :
                      modeAffichage == 2 ? "Mode texte amélioré 1 (ASCII)" :
                                           "Mode texte amélioré 2 (Unicode)")
                  << std::endl;
    } else {
        std::cout << "Erreur : Mode d'affichage invalide.\n";
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
        std::cout << "Démarrage de l'algorithme : Main Droite\n";
        d_robot->appliquerMainDroite(d_terrain,d_modeAffichage);
    } else if (d_algorithmeChoisi == 2) {
        std::cout << "Démarrage de l'algorithme : Pledge\n";
        d_robot->appliquerPledge(d_terrain,d_modeAffichage);
    }

    if (d_stats) {
        std::cout << "Nombre total de cases parcourues : "
                  << d_stats->obtenirNombreCasesParcourues() << std::endl;
    }

    std::cout << "Jeu terminé.\n";
}

void labyrinthe::afficherMenu() {
    int choix = 0;

    while (choix != 5) {
        std::cout << "\n=== Menu Labyrinthe ===\n";
        std::cout << "1. Charger un terrain\n";
        std::cout << "2. Choisir un algorithme\n";
        std::cout << "3. Choisir un mode d'affichage\n";
        std::cout << "4. Lancer le jeu\n";
        std::cout << "5. Quitter\n";
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
                int modeAffichage;
                std::cout << "Choisissez un mode d'affichage :\n";
                std::cout << "1. Mode texte simple\n";
                std::cout << "2. Mode texte amélioré 1 (ASCII)\n";
                std::cout << "3. Mode texte amélioré 2 (Unicode)\n";
                std::cout << "Votre choix : ";
                std::cin >> modeAffichage;
                choisirModeAffichage(modeAffichage);
                break;
            }
            case 4: {
                lancerJeu();
                break;
            }
            case 5: {
                std::cout << "Au revoir !\n";
                exit(0);
            }
            default:
                std::cout << "Erreur : Option invalide.\n";
        }
    }
}
