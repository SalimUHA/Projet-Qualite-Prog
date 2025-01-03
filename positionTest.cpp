//
// Created by Sabri  on 03/01/2025.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "position.h"

TEST_CASE("Test constructeur par défaut") {
    position pos;
    REQUIRE_EQ(pos.x(), 0.0);
    REQUIRE_EQ(pos.y(), 0.0);
}

TEST_CASE("Test constructeur avec paramètres") {
    position pos(5.0, -3.0);
    REQUIRE_EQ(pos.x(), 5.0);
    REQUIRE_EQ(pos.y(), -3.0);
}

TEST_CASE("Test deplaceEn") {
    position pos;
    pos.deplaceEn(10.0, 20.0);
    REQUIRE_EQ(pos.x(), 10.0);
    REQUIRE_EQ(pos.y(), 20.0);
}

TEST_CASE("Test deplaceDe") {
    position pos(5.0, 5.0);
    pos.deplaceDe(2.0, -3.0);
    CHECK_EQ(pos.x(), 7.0);
    CHECK_EQ(pos.y(), 2.0);
}

TEST_CASE("Test distance entre deux positions") {
    position pos1(0.0, 0.0);
    position pos2(3.0, 4.0);
    REQUIRE_EQ(pos1.distance(pos2), doctest::Approx(5.0));
}

TEST_CASE("Test opérateur +") {
    position pos1(1.0, 2.0);
    position pos2(3.0, 4.0);
    position resultat = pos1 + pos2;
    REQUIRE_EQ(resultat.x(), 4.0);
    REQUIRE_EQ(resultat.y(), 6.0);
}

TEST_CASE("Test opérateur +=") {
    position pos(1.0, 1.0);
    pos += position(2.0, 3.0);
    REQUIRE_EQ(pos.x(), 3.0);
    REQUIRE_EQ(pos.y(), 4.0);
}

TEST_CASE("Test opérateur /") {
    position pos(4.0, 6.0);
    position resultat = pos / 2.0;
    CHECK_EQ(resultat.x(), 2.0);
    CHECK_EQ(resultat.y(), 3.0);
}

TEST_CASE("Test opérateur /=") {
    position pos(4.0, 6.0);
    pos /= 2.0;
    REQUIRE_EQ(pos.x(), 2.0);
    REQUIRE_EQ(pos.y(), 3.0);
}

TEST_CASE("Test opérateur * avec ratio à gauche") {
    position pos(2.0, 3.0);
    position resultat = 2.0 * pos;
    CHECK_EQ(resultat.x(), 4.0);
    CHECK_EQ(resultat.y(), 6.0);
}

TEST_CASE("Test affichage de position") {
    position pos(7.5, -2.5);
    std::ostringstream oss;
    oss << pos;
    REQUIRE_EQ(oss.str(), "(7.5,-2.5)");
}

TEST_CASE("Test lecture de position") {
    std::istringstream iss("(3.0,4.0)");
    position pos;
    iss >> pos;
    REQUIRE_EQ(pos.x(), 3.0);
    REQUIRE_EQ(pos.y(), 4.0);
}
