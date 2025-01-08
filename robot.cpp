
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
/*
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
*/
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
bool robot::detecterObstacle(const terrain& t) const
{
    position devant = calculerPositionRelative("DEVANT");
    //return t.obtenirCellule(prochainePosition).estMur();
    return devant.x() >= 0 && devant.x() < t.obtenirLargeur() &&
                              devant.y() >= 0 && devant.y() < t.obtenirHauteur() &&
                              t.estLibre(devant.x(), devant.y());

}

/*
bool robot::dete
cterObstacle(const terrain& t) const {
    position prochainePosition = calculerPositionRelative("DEVANT");

    // Vérifie si la position est hors limites
    if (prochainePosition.x() < 0 || prochainePosition.x() >= t.obtenirLargeur() ||
        prochainePosition.y() < 0 || prochainePosition.y() >= t.obtenirHauteur()) {
        return true; // Considérer hors limites comme obstacle
    }

    // Vérifie si la cellule est un mur
    return t.obtenirCellule(prochainePosition).estMur();
}
*/
bool robot::detecterObstacleADroite(const terrain& t) const
{
    position droite = calculerPositionRelative("DROITE");
    //return t.obtenirCellule(prochainePosition).estMur();
     return droite.x() >= 0 && droite.x() < t.obtenirLargeur() &&
                              droite.y() >= 0 && droite.y() < t.obtenirHauteur() &&
                              t.estLibre(droite.x(), droite.y());
}

bool robot::detecterObstacleAGauche(const terrain& t) const
{
    position prochainePosition = calculerPositionRelative("GAUCHE");
    return t.obtenirCellule(prochainePosition).estMur();
}


void robot::appliquerMainDroite(terrain& t, int modeAffichage) {
    while (!t.obtenirCellule(d_position).estArrivee()) {
        std::cout << "Appuyez sur une touche pour continuer..." << std::endl;
        _getch();

       /* // Positions relatives
        position droite = calculerPositionRelative("DROITE");
        position devant = calculerPositionRelative("DEVANT");

        // Détection des obstacles
        bool droiteEstLibre = droite.x() >= 0 && droite.x() < t.obtenirLargeur() &&
                              droite.y() >= 0 && droite.y() < t.obtenirHauteur() &&
                              t.estLibre(droite.x(), droite.y());

        bool devantEstLibre = devant.x() >= 0 && devant.x() < t.obtenirLargeur() &&
                              devant.y() >= 0 && devant.y() < t.obtenirHauteur() &&
                              t.estLibre(devant.x(), devant.y());
        */
        // Logique de déplacement
        if (detecterObstacleADroite(t)) {
            tournerDroite();
            avancerUneCase(t);
        } else if (detecterObstacle(t)) {
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


/*
void robot::appliquerPledge(terrain& t) {
    int compteurRotation = 0;

    while (!t.obtenirCellule(d_position).estArrivee()) {
        std::cout << "Appuyez sur une touche pour continuer..." << std::endl;
        _getch(); // Attente de l'utilisateur avant chaque étape

        if (compteurRotation == 0) {
            // Avance tant qu'il n'y a pas d'obstacle
            if (!detecterObstacle(t)) {
                avancerUneCase();
                t.afficherTerrain(d_position);
            } else {
                // Rencontre un obstacle, tourne à droite et ajuste le compteur
                tournerDroite();
                compteurRotation--;
            }
        } else {
            // Suivre le mur si compteurRotation != 0
            if (!detecterObstacleADroite(t)) {
                // Pas d'obstacle à droite, tourner à droite et avancer
                tournerDroite();
                compteurRotation--;
                t.afficherTerrain(d_position); // Affichage après rotation
            } else if (!detecterObstacle(t)) {
                // Pas d'obstacle devant, avancer tout droit
                avancerUneCase();
                t.afficherTerrain(d_position); // Affichage après déplacement
            } else {
                // Obstacle devant, tourner à gauche
                tournerGauche();
                compteurRotation++;
                t.afficherTerrain(d_position); // Affichage après rotation
            }
        }

        // Affiche les informations de débogage
        std::cout << "Position: (" << d_position.x() << ", " << d_position.y() << "), Direction: "
                  << d_direction << ", CompteurRotation: " << compteurRotation << std::endl;
    }

    std::cout << "Arrivé à la destination avec l'algorithme de Pledge." << std::endl;
}
*/
/*
void robot::appliquerPledge(terrain& t) {
    int compteurRotation = 0;

    while (!t.obtenirCellule(d_position).estArrivee()) {
        // Si le compteur de rotation est 0, on avance tout droit
        if (compteurRotation == 0) {
            while (!detecterObstacle(t)) {
                avancerUneCase();
                t.afficherTerrain(d_position);

                // Vérifie après chaque mouvement si on est arrivé
                if (t.obtenirCellule(d_position).estArrivee()) {
                    std::cout << "Arrivé à la destination avec l'algorithme de Pledge." << std::endl;
                    return;
                }
            }
            // Rencontre un mur, tourne à droite et ajuste le compteur
            tournerDroite();
            compteurRotation--;
        } else {
            // Suivre le mur si le compteur de rotation n'est pas 0
            if (!detecterObstacleADroite(t)) {
                // Tourne à droite, ajuste le compteur, et avance
                tournerDroite();
                compteurRotation--;
                avancerUneCase();
            } else if (!detecterObstacle(t)) {
                // Pas d'obstacle devant, avance
                avancerUneCase();
            } else {
                // Rencontre un mur, tourne à gauche et ajuste le compteur
                tournerGauche();
                compteurRotation++;
            }
        }

        // Affiche l'état actuel du terrain
        t.afficherTerrain(d_position);
    }

    std::cout << "Arrivé à la destination avec l'algorithme de Pledge." << std::endl;
}
*/
/*
void robot::appliquerPledge(terrain& t) {
    int compteurRotation = 0; // Compteur pour suivre les rotations

    while (!t.obtenirCellule(d_position).estArrivee()) {
        std::cout << "Appuyez sur une touche pour continuer..." << std::endl;
        _getch();

        // Positions relatives
        position droite = calculerPositionRelative("DROITE");
        position devant = calculerPositionRelative("DEVANT");

        // Détection des obstacles
        bool droiteEstLibre = droite.x() >= 0 && droite.x() < t.obtenirLargeur() &&
                              droite.y() >= 0 && droite.y() < t.obtenirHauteur() &&
                              t.estLibre(droite.x(), droite.y());

        bool devantEstLibre = devant.x() >= 0 && devant.x() < t.obtenirLargeur() &&
                              devant.y() >= 0 && devant.y() < t.obtenirHauteur() &&
                              t.estLibre(devant.x(), devant.y());

        // Logique de déplacement
        if (compteurRotation == 0) {
            // Si le compteur est à 0, avancer tout droit si possible
            if (devantEstLibre) {
                avancerUneCase(t);
            } else {
                tournerDroite();
                compteurRotation--;
            }
        } else {
            // Suivre le mur
            if (droiteEstLibre) {
                tournerDroite();
                compteurRotation--;
                avancerUneCase(t);
            } else if (devantEstLibre) {
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

        t.afficherTerrain(d_position);

        // Afficher les informations pour le débogage
        std::cout << "Position actuelle : (" << d_position.x() << ", " << d_position.y() << ")\n";
        std::cout << "Direction actuelle : " << d_direction << "\n";
        std::cout << "CompteurRotation : " << compteurRotation << "\n";
    }

    std::cout << "Arrivé à la destination avec l'algorithme de Pledge." << std::endl;
}*/

void robot::appliquerPledge(terrain& t,int modeAffichage) {
    int compteurRotation = 0; // Compteur des changements de direction

    while (!t.obtenirCellule(d_position).estArrivee()) {
        std::cout << "Appuyez sur une touche pour continuer..." << std::endl;
        _getch();

        // Positions relatives
        position droite = calculerPositionRelative("DROITE");
        position devant = calculerPositionRelative("DEVANT");

        // Détection des obstacles
        bool droiteEstLibre = droite.x() >= 0 && droite.x() < t.obtenirLargeur() &&
                              droite.y() >= 0 && droite.y() < t.obtenirHauteur() &&
                              t.estLibre(droite.x(), droite.y());

        bool devantEstLibre = devant.x() >= 0 && devant.x() < t.obtenirLargeur() &&
                              devant.y() >= 0 && devant.y() < t.obtenirHauteur() &&
                              t.estLibre(devant.x(), devant.y());

        // Instruction 1 : Avancer tout droit tant que possible
        if (compteurRotation == 0) {
            if (devantEstLibre) {
                avancerUneCase(t);
            } else {
                tournerDroite();
                compteurRotation--; // Mur rencontré, commencer à longer le mur
            }
        }
        // Instruction 2 : Longer le mur
        else {
            if (droiteEstLibre) {
                tournerDroite();
                compteurRotation--;
                avancerUneCase(t);
            } else if (devantEstLibre) {
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
