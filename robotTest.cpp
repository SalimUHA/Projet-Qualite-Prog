//
// Created by SAID on 03/01/2025.
//

#include <stdexcept>
#include <iostream>
#include <vector>
using namespace std;

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "robot.h"
#include "position.h"
#include "terrain.h"
#include "celulle.h"
#include "observateurConsole.h"

TEST_CASE("Tests de la classe robot") {
    terrain t{5, 5};

    SUBCASE("Création du robot") {
        SUBCASE("Création réussie dans une cellule libre") {
            robot r{position{2, 3}};
            REQUIRE_EQ(r.obtenirPosition(), position{2, 3});
            REQUIRE_EQ(t.obtenirCellule(position{2, 3}).estVide(), true);
        }

        SUBCASE("Échec si la position initiale est occupée") {
            position p{1, 1};
            t.obtenirCellule(p).rendreMur();
            CHECK_THROWS_AS(robot{p}, runtime_error);
        }

        SUBCASE("Échec si la position initiale est hors du terrain") {
            position p{10, 10};
            CHECK_THROWS_AS(robot{p}, out_of_range);
        }
    }

    SUBCASE("Déplacements du robot") {
        robot r{position{0, 0}};
        position p{1, 1};
        SUBCASE("Déplacement valide vers une cellule libre") {
            r.deplacer(p);
            REQUIRE_EQ(r.obtenirPosition(), p);
            REQUIRE_EQ(t.obtenirCellule(position{0, 0}).estVide(), true);
            REQUIRE_EQ(t.obtenirCellule(position{1, 1}).estVide(), false);
        }

        SUBCASE("Déplacement invalide vers une cellule occupée") {
            t.obtenirCellule(position{1, 1}).rendreMur();
            CHECK_THROWS_AS(r.deplacer(position{1, 1}), runtime_error);
        }

        SUBCASE("Déplacement invalide hors du terrain") {
            CHECK_THROWS_AS(r.deplacer(position{-1, 0}), out_of_range);
        }
    }

    SUBCASE("Interaction avec le terrain") {
        robot r{position{2, 2}};

        SUBCASE("Le robot libère correctement une cellule après déplacement") {
            r.deplacer(position{3, 3});
            REQUIRE_EQ(t.obtenirCellule(position{2, 2}).estVide(), true);
            REQUIRE_EQ(t.obtenirCellule(position{3, 3}).estVide(), false);
        }

        SUBCASE("Le robot détecte une cellule occupée") {
            t.obtenirCellule(position{4, 4}).rendreMur();
            CHECK_THROWS_AS(r.deplacer(position{4, 4}), runtime_error);
        }
    }

    SUBCASE("Gestion des observateurs") {
        robot r{position{0, 0}};
        observateurConsole obs1;
        observateurConsole obs2;

        SUBCASE("Ajout et notification des observateurs") {
            r.ajouterObservateur(&obs1);
            r.ajouterObservateur(&obs2);
            r.notifierObservateurs();
            REQUIRE_EQ(obs1.getNotifications(), 1);
            REQUIRE_EQ(obs2.getNotifications(), 1);
        }

        SUBCASE("Suppression des observateurs") {
            r.ajouterObservateur(&obs1);
            r.ajouterObservateur(&obs2);
            r.supprimerObservateur(&obs1);
            r.notifierObservateurs();
            REQUIRE_EQ(obs1.getNotifications(), 0);
            REQUIRE_EQ(obs2.getNotifications(), 1);
        }
    }

    SUBCASE("Détection d'obstacle") {
        robot r{position{3, 3}};

        SUBCASE("Aucun obstacle détecté") {
            REQUIRE_EQ(r.detecterObstacle(t), false);
        }

        SUBCASE("Obstacle détecté après déplacement") {
            position murPos{3, 4};
            t.definirMur(murPos);
            r.deplacer(position{3, 4});
            REQUIRE_EQ(r.detecterObstacle(t), true);
        }
    }
}
