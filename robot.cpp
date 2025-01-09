
#include "robot.h"
#include "Terrain.h"
#include <algorithm>
#include <conio.h>

robot::robot(const position& startPos)
    : d_position(startPos), d_direction("NORD") {}

position robot::obtenirPosition() const {
    return d_position;
}

std::string robot::obtenirDirection() const {
    return d_direction;
}

void robot::deplacer(const position& nouvellePosition){
    d_position.deplaceEn(nouvellePosition.x(),nouvellePosition.y());
    notifierObservateurs();
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

void robot::avancerUneCase(terrain& t) {
        position prochainePosition = calculerPositionRelative("DEVANT");
        d_position = prochainePosition; // Met à jour la position
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
bool robot::devantEstLibre(const terrain& t) const
{
    position devant = calculerPositionRelative("DEVANT");

    return devant.x() >= 0 && devant.x() < t.obtenirLargeur() &&
                              devant.y() >= 0 && devant.y() < t.obtenirHauteur() &&
                              t.estLibre(devant.x(), devant.y());

}


bool robot::droiteEstLibre(const terrain& t) const
{
    position droite = calculerPositionRelative("DROITE");
     return droite.x() >= 0 && droite.x() < t.obtenirLargeur() &&
                              droite.y() >= 0 && droite.y() < t.obtenirHauteur() &&
                              t.estLibre(droite.x(), droite.y());
}

bool robot::gaucheEstLibre(const terrain& t) const
{
    position gauche = calculerPositionRelative("GAUCHE");
     return gauche.x() >= 0 && gauche.x() < t.obtenirLargeur() &&
                              gauche.y() >= 0 && gauche.y() < t.obtenirHauteur() &&
                              t.estLibre(gauche.x(), gauche.y());

}


void robot::appliquerMainDroite(terrain& t, int modeAffichage) {
    while (!t.obtenirCellule(d_position).estArrivee()) {
        std::cout << "Appuyez sur une touche pour continuer..." << std::endl;
        _getch();

        if (droiteEstLibre(t)) {
            tournerDroite();
            avancerUneCase(t);
        } else if (devantEstLibre(t)) {
            avancerUneCase(t);
        } else {
            tournerGauche();
        }

        // Mise à jour et affichage du terrain
        if (!t.obtenirCellule(d_position).estMur()) {
            t.obtenirCellule(d_position).rendreRobot();
        }

        t.afficherTerrain(d_position,d_direction,modeAffichage);
    }

    std::cout << "Arrivé à la destination avec l'algorithme de la Main Droite." << std::endl;

}

void robot::appliquerPledge(terrain& t,int modeAffichage) {
    int compteurRotation = 0; // Compteur des changements de direction

    while (!t.obtenirCellule(d_position).estArrivee()) {
        std::cout << "Appuyez sur une touche pour continuer..." << std::endl;
        _getch();

        // Instruction 1 : Avancer tout droit tant que possible
        if (compteurRotation == 0) {
            if (devantEstLibre(t)) {
                avancerUneCase(t);
            } else {
                tournerDroite();
                compteurRotation--; // Mur rencontré, commencer à longer le mur
            }
        }
        // Instruction 2 : Longer le mur
        else {
            if (droiteEstLibre(t)) {
                tournerDroite();
                compteurRotation--;
                avancerUneCase(t);
            } else if (devantEstLibre(t)) {
                avancerUneCase(t);
            } else {
                tournerGauche();
                compteurRotation++;
            }
        }

        // Mise à jour et affichage du terrain
        if (!t.obtenirCellule(d_position).estMur()) {
            t.obtenirCellule(d_position).rendreRobot();
        }

        t.afficherTerrain(d_position,d_direction,modeAffichage);

        // Afficher les informations de débogage
        std::cout << "Position actuelle : (" << d_position.x() << ", " << d_position.y() << ")\n";
        std::cout << "Direction actuelle : " << d_direction << "\n";
        std::cout << "CompteurRotation : " << compteurRotation << "\n";
    }

    std::cout << "Arrivé à la destination avec l'algorithme de Pledge." << std::endl;
}
