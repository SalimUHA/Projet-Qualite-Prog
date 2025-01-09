//
// Created by sabri on 11/12/2024.
//

#ifndef ROBOT_H
#define ROBOT_H
#include <iostream>
#include <vector>
#include "Position.h"
#include "Celulle.h"
#include "Observateur.h"
#include "Terrain.h"
#include "observateurStatistiques.h"

class robot {
public:
	robot(const position& startPos);

    position obtenirPosition() const;
    std::string obtenirDirection() const;

    // Gestion des déplacements
    void deplacer(const position& nouvellePosition);
	void avancerUneCase(terrain &t);
	void tournerDroite();
	void tournerGauche();

    // Gestion des observateurs
    void ajouterObservateur(observateur* obs);
    void supprimerObservateur(observateur* obs);
    void notifierObservateurs();

    // Calcul des positions relatives
    position calculerPositionRelative(const std::string& directionRelative) const;

    // Détection des obstacles
    bool devantEstLibre(const terrain& terrain) const;
    bool droiteEstLibre(const terrain& t) const;
    bool gaucheEstLibre(const terrain& t) const;

    // Algorithmes de labyrinthe
    void appliquerMainDroite(terrain& t,int modeAffichage);
    void appliquerPledge(terrain& t,int modeAffichage);


private:
	position d_position;
	std::string d_direction;
    std::vector<observateur*> d_observateurs;
};



#endif //ROBOT_H
