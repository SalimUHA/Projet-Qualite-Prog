#ifndef OBSERVATEURSTATISTIQUES_H_INCLUDED
#define OBSERVATEURSTATISTIQUES_H_INCLUDED

#include "observateur.h"
#include "Position.h"

class observateurStatistiques : public observateur {
public:
    observateurStatistiques(const position &depart);
    void miseAJour(const position& pos, const std::string& direction) override;
    int obtenirNombreCasesParcourues() const;

private:
    position d_dernierePosition;
    int d_nombreCasesParcourues;
};

#endif // OBSERVATEURSTATISTIQUES_H_INCLUDED
