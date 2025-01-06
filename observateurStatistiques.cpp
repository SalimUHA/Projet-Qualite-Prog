#include "observateurStatistiques.h"
#include <iostream>

observateurStatistiques::observateurStatistiques(const position &depart):
    d_nombreCasesParcourues(0), d_dernierePosition(depart)
{
}

void observateurStatistiques::miseAJour(const position& pos, const std::string& direction)
{
    if (d_dernierePosition.x() != -1 && d_dernierePosition != pos)
    {
        d_nombreCasesParcourues++;
    }

    d_dernierePosition = pos;

}

int observateurStatistiques::obtenirNombreCasesParcourues() const
{
    return d_nombreCasesParcourues;
}
