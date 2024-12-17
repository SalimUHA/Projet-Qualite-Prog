//
// Created by sabri on 11/12/2024.
//

#ifndef ROBOT_H
#define ROBOT_H
#include <iostream>
#include <vector>
#include "Position.h"
#include "Celulle.h"

class robot {
public:
	Robot(int largeur, int hauteur); // Constructeur d'un robot
	void avancerUneCase();
	void tournerDroite(int angle);
	void tournerGauche(int angle);
	void notifieObservateur(const Position pos, )

private:
	Position d_position;
	
	observateurRobot d_obsRobot;

};



#endif //ROBOT_H
