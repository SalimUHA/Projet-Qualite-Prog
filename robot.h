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

class robot {
public:
	robot(const position& startPos);

	void avancerUneCase();
	void tournerDroite();
	void tournerGauche();

    void ajouterObservateur(observateur* obs);
    void supprimerObservateur(observateur* obs);
    void notifierObservateurs();

    bool detecterObstacle(const terrain& terrain) const;


private:
	Position d_position;
	std::string d_direction;
    std::vector<Observateur*> d_observateurs;
};



#endif //ROBOT_H
