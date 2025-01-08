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
    void deplacer(const position& nouvellePos);
	void avancerUneCase(terrain &t);
	void tournerDroite();
	void tournerGauche();

    void ajouterObservateur(observateur* obs);
    void supprimerObservateur(observateur* obs);
    void notifierObservateurs();
    position calculerPositionRelative(const std::string& directionRelative) const;
    bool detecterObstacle(const terrain& terrain) const;
    bool detecterObstacleADroite(const terrain& t) const;
    bool detecterObstacleAGauche(const terrain& t) const;
    void appliquerMainDroite(terrain& t,int modeAffichage);
    void appliquerPledge(terrain& t,int modeAffichage);


private:
	position d_position;
	std::string d_direction;
    std::vector<observateur*> d_observateurs;
};



#endif //ROBOT_H
