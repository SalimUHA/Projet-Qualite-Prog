#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "terrain.h"
#include "position.h"
#include "celulle.h"

TEST_CASE("Tests de la classe terrain") {
    SUBCASE("Construction et dimensions du terrain") {
        terrain t{10, 5};
        REQUIRE_EQ(t.obtenirLargeur(), 10);
        REQUIRE_EQ(t.obtenirHauteur(), 5);
    }

    SUBCASE("Définition et récupération des cellules") {
        terrain t{10, 5};
        position pos{3, 3};
        cellule mur{CELLULE_MUR};
        cellule vide{CELLULE_VIDE};

        t.definirMur(pos);
        REQUIRE_EQ(t.obtenirCellule(pos).obtenirType(), mur.obtenirType());

        position posVide{2, 2};
        REQUIRE_EQ(t.obtenirCellule(posVide).obtenirType(), vide.obtenirType());
    }

    SUBCASE("Définir et obtenir la position de départ et d'arrivée") {
        terrain t{10, 5};
        position depart{0, 0};
        position arrivee{9, 4};

        t.definirDepart(depart);
        t.definirArrivee(arrivee);

        REQUIRE_EQ(t.obtenirPositionDepart(), depart);
        REQUIRE_EQ(t.obtenirPositionArrivee(), arrivee);
    }

    SUBCASE("Chargement et sauvegarde d'un terrain depuis/vers un fichier") {
        terrain t{10, 5};
        position mur{1, 1};
        position depart{0, 0};
        position arrivee{9, 4};

        t.definirMur(mur);
        t.definirDepart(depart);
        t.definirArrivee(arrivee);

        t.sauvegarderDansFichier("terrain_test.txt");

        terrain t2{10, 5};
        t2.chargerDepuisFichier("terrain_test.txt");

        REQUIRE_EQ(t2.obtenirCellule(mur).obtenirType(), CELLULE_MUR);
        REQUIRE_EQ(t2.obtenirPositionDepart(), depart);
        REQUIRE_EQ(t2.obtenirPositionArrivee(), arrivee);
    }

    SUBCASE("Affichage du terrain") {
        terrain t{5, 5};
        position mur{2, 2};
        t.definirMur(mur);
        t.afficherTerrain();
        // Vérification visuelle (ou implémentation de la capture de sortie pour automatiser le test).
    }
}
