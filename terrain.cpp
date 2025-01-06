//
// Created by salim on 11/12/2024.
//

#include "terrain.h"

terrain::terrain(int largeur, int hauteur):
 d_largeur(largeur), d_hauteur(hauteur)
{
  d_grille.resize(hauteur, std::vector<cellule>(largeur,cellule()));
}

void terrain::initialiserTerrain(int largeur, int hauteur)
{
    d_largeur = largeur;
    d_hauteur = hauteur;
    d_grille.clear();
    d_grille.resize(hauteur, std::vector<cellule>(largeur, cellule()));
}
int terrain::obtenirLargeur() const
{
    return d_largeur;
}
int terrain::obtenirHauteur() const
{
    return d_hauteur;
}

cellule terrain::obtenirCellule(const position &pos) const
{
    return d_grille[pos.y()][pos.x()];
}

position terrain::obtenirPositionDepart() const
{
  position depart;
  int i = 0, j = 0;
  bool trouve = false;

  while (i < d_hauteur && !trouve) {
    j = 0;
    while (j < d_largeur && !trouve) {
      if (d_grille[i][j].estDepart()) {
        depart.deplaceEn(i, j);
        trouve = true;
      }
      j++;
    }
    i++;
  }

  return depart;
}

position terrain::obtenirPositionArrivee() const
{
  position arrivee;
  int i = 0, j = 0;
  bool trouve = false;

  while (i < d_hauteur && !trouve) {
    j = 0;
    while (j < d_largeur && !trouve) {
      if (d_grille[i][j].estArrivee()) {
        arrivee.deplaceEn(i, j);
        trouve = true;
      }
      j++;
    }
    i++;
  }

  return arrivee;
}

void terrain::definirMur(const position &pos)
{
  d_grille[pos.y()][pos.x()].rendreMur();
}

void terrain::definirDepart(const position &pos)
{
  d_grille[pos.y()][pos.x()].rendreDepart();
}

void terrain::definirArrivee(const position &pos)
{
  d_grille[pos.y()][pos.x()].rendreArrivee();
}

void terrain::afficherTerrain() const
      {
    for (int i = 0; i < d_hauteur; ++i)
  {
      for (int j = 0; j < d_largeur; ++j)
      {
        d_grille[i][j].afficherCellule();
      }
      std::cout << std::endl;
    }
  }


void terrain::afficherTerrain(const position& robotPos) const {
    for (int y = 0; y < d_hauteur; ++y) {
        for (int x = 0; x < d_largeur; ++x) {
            if (robotPos.x() == x && robotPos.y() == y) {
                std::cout << 'R'; // Repr�sentation du robot
            } else {
                d_grille[y][x].afficherCellule();
            }
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void terrain::sauvegarderDansFichier(const std::string &nomFichier) const
{
    std::ofstream fichier(nomFichier);

    if(!fichier)
    {
        std::cout<<"Erreur, impossible d'ouvrir le fichier du nom de : "<<nomFichier;
        return;
    }

    fichier << d_largeur << " " << d_hauteur << "\n";

    for (int i = 0; i < d_hauteur; ++i)
    {
        for (int j = 0; j < d_largeur; ++j)
        {
            fichier << d_grille[i][j].obtenirCaractere();
        }
        fichier << "\n";
    }

    fichier.close();

}

void terrain::chargerDepuisFichier(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);

    if (!fichier)
    {
        std::cout << "erreur, impossible d'ouvrir le fichier " << nomFichier << std::endl;
        return;
    }

    int largeur, hauteur;
    fichier >> largeur >> hauteur;

    if (fichier.fail())
    {
        std::cout<< "erreur, impossible de lire les dimensions du terrain dans le fichier " << nomFichier << std::endl;
        return;
    }


    initialiserTerrain(largeur, hauteur);

    for (int i = 0; i < d_hauteur; ++i)
    {
        for (int j = 0; j < d_largeur; ++j)
        {
            char type;
            fichier >> type;

            if (fichier.fail())
            {
                std::cout << "erreur, caractere invalide ou incomplete" << std::endl;
                return;
            }

            d_grille[i][j].initialiserDepuisCaractere(type);
            if (type == 'R') {
                d_robotPos = {j, i};
            }
        }
    }

    fichier.close();
}

bool terrain::estLibre(int x, int y) const
{

    return x >= 0 && x < d_grille.size() && y >= 0 && y < d_grille[0].size() && d_grille[x][y] == ' ';
}

char terrain::getCase(int x, int y) const
{

    return d_grille[x][y];
}