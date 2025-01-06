
#include "robot.h"
#include "Terrain.h"
#include <algorithm>
#include <conio.h>

robot::robot(const position& startPos)
    : d_position(startPos), d_direction("NORD") {}

position robot::obtenirPosition() const {
    return d_position;
}

void robot::deplacer(const position& nouvellePos){
    d_position.deplaceEn(nouvellePos.x(),nouvellePos.y());
}
void robot::ajouterObservateur(observateur* obs) {
    d_observateurs.push_back(obs);
}

void robot::supprimerObservateur(observateur* obs) {
    auto it = std::remove(d_observateurs.begin(), d_observateurs.end(), obs);
    if (it != d_observateurs.end()) {
        d_observateurs.erase(it, d_observateurs.end());
    }
}


void robot::notifierObservateurs()
{
    for (auto* obs : d_observateurs)
        {
        obs->miseAJour(d_position, d_direction);
        }
}

void robot::avancerUneCase() {
    if (d_direction == "NORD") {
        d_position.deplaceDe(0, -1);
    } else if (d_direction == "EST") {
        d_position.deplaceDe(1, 0);
    } else if (d_direction == "SUD") {
        d_position.deplaceDe(0, 1);
    } else if (d_direction == "OUEST") {
        d_position.deplaceDe(-1, 0);
    }

    notifierObservateurs();
}

void robot::tournerDroite() {
    if (d_direction == "NORD") d_direction = "EST";
    else if (d_direction == "EST") d_direction = "SUD";
    else if (d_direction == "SUD") d_direction = "OUEST";
    else if (d_direction == "OUEST") d_direction = "NORD";

    notifierObservateurs();
}

void robot::tournerGauche() {
    if (d_direction == "NORD") d_direction = "OUEST";
    else if (d_direction == "OUEST") d_direction = "SUD";
    else if (d_direction == "SUD") d_direction = "EST";
    else if (d_direction == "EST") d_direction = "NORD";

    notifierObservateurs();
}

position robot::calculerPositionRelative(const std::string& directionRelative) const
{
    position prochainePosition = d_position;

    if (directionRelative == "DEVANT")
    {
        if (d_direction == "NORD")
        {
            prochainePosition.deplaceDe(0, -1);
        }
        else if (d_direction == "EST")
        {
            prochainePosition.deplaceDe(1, 0);
        }
        else if (d_direction == "SUD")
        {
            prochainePosition.deplaceDe(0, 1);
        }
        else if (d_direction == "OUEST")
        {
            prochainePosition.deplaceDe(-1, 0);
        }
    }
    else if (directionRelative == "DROITE")
    {
        if (d_direction == "NORD")
        {
            prochainePosition.deplaceDe(1, 0);
        }
        else if (d_direction == "EST")
        {
            prochainePosition.deplaceDe(0, 1);
        }
        else if (d_direction == "SUD")
        {
            prochainePosition.deplaceDe(-1, 0);
        }
        else if (d_direction == "OUEST")
        {
            prochainePosition.deplaceDe(0, -1);
        }
    }
    else if (directionRelative == "GAUCHE")
    {
        if (d_direction == "NORD")
        {
            prochainePosition.deplaceDe(-1, 0);
        }
        else if (d_direction == "EST")
        {
            prochainePosition.deplaceDe(0, -1);
        }
        else if (d_direction == "SUD")
        {
            prochainePosition.deplaceDe(1, 0);
        }
        else if (d_direction == "OUEST")
        {
            prochainePosition.deplaceDe(0, 1);
        }
    }

    return prochainePosition;
}
bool robot::detecterObstacle(const terrain& t) const
{
    position prochainePosition = calculerPositionRelative("DEVANT");
    return t.obtenirCellule(prochainePosition).estMur();
}

bool robot::detecterObstacleADroite(const terrain& t) const
{
    position prochainePosition = calculerPositionRelative("DROITE");
    return t.obtenirCellule(prochainePosition).estMur();
}

bool robot::detecterObstacleAGauche(const terrain& t) const
{
    position prochainePosition = calculerPositionRelative("GAUCHE");
    return t.obtenirCellule(prochainePosition).estMur();
}

void robot::appliquerMainDroite(terrain& t)
{
    while (!t.obtenirCellule(d_position).estArrivee()) {
        std::cout << "Appuyez sur une touche pour continuer..." << std::endl;
        _getch();

        if (!t.obtenirCellule(d_position).estMur())
            {
            t.obtenirCellule(d_position).rendreVide();
        }


        t.afficherTerrain(d_position);

        if (!detecterObstacle(t))
            {
            avancerUneCase();
            }
        else
            {
            tournerGauche();
            t.afficherTerrain(d_position);
            if (!detecterObstacle(t))
                {
                avancerUneCase();
                }
            else
                {
                    tournerGauche();
                    t.afficherTerrain(d_position);
                }
            }

        if (!t.obtenirCellule(d_position).estMur()) {
            t.obtenirCellule(d_position).rendreRobot();
        }

        t.afficherTerrain(d_position);
    }
    std::cout << "Arrive à la destination avec l'algorithme de la main droite." << std::endl;
}

void robot::appliquerPledge(terrain& t)
{
    int compteurRotation = 0;

    while (!t.obtenirCellule(d_position).estArrivee())
    {
        if (compteurRotation == 0)
        {
            while (!detecterObstacle(t))
            {
                std::cout << "Appuyez sur une touche pour continuer..." << std::endl;
                _getch(); // Attendre une entrée de l'utilisateur pour avancer
                avancerUneCase();
                t.afficherTerrain(d_position);
            }
            tournerDroite();
            compteurRotation--;
        }
        else
        {
            if (!detecterObstacleADroite(t))
            {
                tournerDroite();
                compteurRotation--;
                avancerUneCase();
            }
            else if (!detecterObstacle(t))
            {
                avancerUneCase();
            }
            else
            {
                tournerGauche();
                compteurRotation++;
            }
        }
        t.afficherTerrain(d_position);
    }
    std::cout << "Arrivé à la destination avec l'algorithme de Pledge." << std::endl;
}





