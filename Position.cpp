//
// Created by salim on 12/12/2024.
//

#include "Position.h"
#include <cmath>
Position::Position(double x,double y):
    d_x{x},d_y{y}
{
}

Position::Position():
    d_x{0.0}, d_y{0.0}
{
}


double Position::x() const
{
    return d_x;
}



double Position::y() const
{
    return d_y;
}

void Position::deplaceEn(double x,double y)
{
    d_x=x;
    d_y=y;
}

void Position::deplaceDe(double x,double y)
{
    d_x+=x;
    d_y+=y;
}

double Position::distance(const Position &p) const
{
    double dx=p.x()-d_x;
    double dy=p.y()-d_y;
    return sqrt(dx*dx+dy*dy);
}


void Position::affiche(std::ostream &ost) const
{
    ost <<'('<<d_x<<','<<d_y<<')';
}

void Position::lit(std::istream &ist)
{
    double x,y;
    char ponctuation;
    ist >>ponctuation>>x>>ponctuation>>y>>ponctuation;
    if (ist.good())
    {
        d_x=x;
        d_y=y;
    }
}

std::istream &operator>>(std::istream &ist, Position &p)
{
    p.lit(ist);
    return ist;
}

std::ostream &operator<<(std::ostream &ost, const Position &p)
{
    p.affiche(ost);
    return ost;
}

Position operator+(const Position &p1, const Position &p2)
{
    Position somme{p1.d_x+p2.d_x,p1.d_y+p2.d_y};
    return somme;
}

Position &Position::operator+=(const Position &p)
{
    d_x+=p.d_x;
    d_y+=p.d_y;
    return *this;
}

Position operator/(const Position &p, double r)
{
    Position division{p.d_x/r,p.d_y/r};
    return division;
}

Position &Position::operator/=(double r)
{
    d_x/=r;
    d_y/=r;
    return *this;
}

Position operator*(double r, const Position &p)
{
    Position multiple{p.x()*r,p.y()*r};
    return multiple;
}
