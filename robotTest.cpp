//
// Created by SAID on 03/01/2025.
//

#include <stdexcept>
#include <iostream>
#include <vector>
using namespace std;

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("Tests optimisés pour la classe Robot") {
    terrain t(5, 5);

    SUBCASE("Création du robot") {
        SUBCASE("Création réussie dans une cellule libre") {
            robot r(&t, position(2, 3));
            REQUIRE_EQ(r.obtenirPosition(), position(2, 3));
            REQUIRE_EQ(t.obtenirCellule(position(2, 3)).estLibre(), false);
        }

        SUBCASE("Échec si la position initiale est occupée") {
            t.obtenirCellule(position(1, 1)).setLibre(false);
            CHECK_THROWS_AS(robot(&t, position(1, 1)), runtime_error);
        }

        SUBCASE("Échec si la position initiale est hors du terrain") {
            CHECK_THROWS_AS(robot(&t, position(10, 10)), out_of_range);
        }
    }

    SUBCASE("Déplacements du robot") {
        robot r(&t, position(0, 0));

        SUBCASE("Déplacement valide vers une cellule libre") {
            r.deplacer(position(1, 1));
            REQUIRE_EQ(r.obtenirPosition(), position(1, 1));
            REQUIRE_EQ(t.obtenirCellule(position(0, 0)).estLibre(), true);
            REQUIRE_EQ(t.obtenirCellule(position(1, 1)).estLibre(), false);
        }

        SUBCASE("Déplacement invalide vers une cellule occupée") {
            t.obtenirCellule(position(1, 1)).setLibre(false);
            CHECK_THROWS_AS(r.deplacer(position(1, 1)), runtime_error);
        }

        SUBCASE("Déplacement invalide hors du terrain") {
            CHECK_THROWS_AS(r.deplacer(position(-1, 0)), out_of_range);
        }
    }

    SUBCASE("Interaction avec le terrain") {
        robot r(&t, position(2, 2));

        SUBCASE("Le robot libère correctement une cellule après déplacement") {
            r.deplacer(position(3, 3));
            REQUIRE_EQ(t.obtenirCellule(position(2, 2)).estLibre(), true);
            REQUIRE_EQ(t.obtenirCellule(position(3, 3)).estLibre(), false);
        }

        SUBCASE("Le robot détecte une cellule occupée") {
            t.obtenirCellule(position(4, 4)).setLibre(false);
            CHECK_THROWS_AS(r.deplacer(position(4, 4)), runtime_error);
        }
    }
}
