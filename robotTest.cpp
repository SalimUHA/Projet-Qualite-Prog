//
// Created by SAID on 03/01/2025.
//

#include <sstream>
#include <stdexcept>


#include "doctest.h"
#include "robot.h"
#include "position.h"
#include "terrain.h"
#include "celulle.h"
#include "observateurConsole.h"
TEST_CASE("Tests de la classe robot") {
    terrain t(10, 10);
    t.definirDepart(position(0, 0));
    t.definirArrivee(position(9, 9));
    robot r(t.obtenirPositionDepart());

    SUBCASE("Initialisation du robot") {
        REQUIRE_EQ(r.obtenirPosition(), position(0, 0));
        REQUIRE_EQ(r.obtenirDirection(), "NORD");
    }

    SUBCASE("Déplacement du robot") {
        SUBCASE("Déplacement valide") {
            position newPos(1, 0);
            r.deplacer(newPos);
            REQUIRE_EQ(r.obtenirPosition(), newPos);
        }

        SUBCASE("Déplacement vers une cellule occupée") {
            t.definirMur(position(1, 0));
            CHECK_THROWS_AS(r.deplacer(position(1, 0)), std::runtime_error);
        }

        SUBCASE("Déplacement hors limites") {
            CHECK_THROWS_AS(r.deplacer(position(-1, 0)), std::out_of_range);
        }
    }

    SUBCASE("Gestion des directions") {
        SUBCASE("Rotation à droite") {
            r.tournerDroite();
            REQUIRE_EQ(r.obtenirDirection(), "EST");

            r.tournerDroite();
            REQUIRE_EQ(r.obtenirDirection(), "SUD");

            r.tournerDroite();
            REQUIRE_EQ(r.obtenirDirection(), "OUEST");

            r.tournerDroite();
            REQUIRE_EQ(r.obtenirDirection(), "NORD");
        }

        SUBCASE("Rotation à gauche") {
            r.tournerGauche();
            REQUIRE_EQ(r.obtenirDirection(), "OUEST");

            r.tournerGauche();
            REQUIRE_EQ(r.obtenirDirection(), "SUD");

            r.tournerGauche();
            REQUIRE_EQ(r.obtenirDirection(), "EST");

            r.tournerGauche();
            REQUIRE_EQ(r.obtenirDirection(), "NORD");
        }
    }

    SUBCASE("Détection d'obstacles") {
        SUBCASE("Obstacle devant") {
            t.definirMur(position(0, 1));
            REQUIRE_FALSE(r.devantEstLibre(t));
        }

        SUBCASE("Pas d'obstacle devant") {
            REQUIRE(r.devantEstLibre(t));
        }

        SUBCASE("Obstacle à droite") {
            r.tournerDroite();
            t.definirMur(position(1, 0));
            REQUIRE_FALSE(r.droiteEstLibre(t));
        }

        SUBCASE("Pas d'obstacle à droite") {
            REQUIRE(r.droiteEstLibre(t));
        }
    }

    SUBCASE("Interaction avec les observateurs") {
        observateurConsole obs;

        // Ajoute l'observateur
        r.ajouterObservateur(&obs);

        // Redirige la sortie standard pour capturer les notifications
        std::ostringstream sortieCapturee;
        std::streambuf* coutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(sortieCapturee.rdbuf());

        // Déplace le robot
        r.deplacer(position(1, 1));
        r.notifierObservateurs();

        // Restaure la sortie standard
        std::cout.rdbuf(coutBuffer);

        REQUIRE_EQ(sortieCapturee.str(), "Position : (1, 1), Direction : NORD\n");
    }

    SUBCASE("Algorithmes de labyrinthe avec mode d'affichage") {
        t.chargerDepuisFichier("labyrinthe_test.txt");

        SUBCASE("Main Droite avec mode d'affichage simple") {
            std::ostringstream sortieCapturee;
            std::streambuf* coutBuffer = std::cout.rdbuf();
            std::cout.rdbuf(sortieCapturee.rdbuf());

            CHECK_NOTHROW(r.appliquerMainDroite(t, 1));

            std::cout.rdbuf(coutBuffer);

            REQUIRE(t.obtenirCellule(r.obtenirPosition()).estArrivee());
            REQUIRE(!sortieCapturee.str().empty()); // Vérifie que l'affichage a été produit
        }

        SUBCASE("Pledge avec mode d'affichage amélioré") {
            std::ostringstream sortieCapturee;
            std::streambuf* coutBuffer = std::cout.rdbuf();
            std::cout.rdbuf(sortieCapturee.rdbuf());

            CHECK_NOTHROW(r.appliquerPledge(t, 2));

            std::cout.rdbuf(coutBuffer);

            REQUIRE(t.obtenirCellule(r.obtenirPosition()).estArrivee());
            REQUIRE(!sortieCapturee.str().empty()); // Vérifie que l'affichage a été produit
        }
    }
}
