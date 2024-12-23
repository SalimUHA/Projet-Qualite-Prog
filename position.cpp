//
// Created by salim on 12/12/2024.
//

#include "position.h"
#include <cmath>
position::position(double x,double y):
    d_x{x},d_y{y}
{
}

position::position():
    d_x{0.0}, d_y{0.0}
{
}


double position::x() const
{
    return d_x;
}



double position::y() const
{
    return d_y;
}

void position::deplaceEn(double x,double y)
{
    d_x=x;
    d_y=y;
}

void position::deplaceDe(double x,double y)
{
    d_x+=x;
    d_y+=y;
}

double position::distance(const position &p) const
{
    double dx=p.x()-d_x;
    double dy=p.y()-d_y;
    return sqrt(dx*dx+dy*dy);
}


void position::affiche(std::ostream &ost) const
{
    ost <<'('<<d_x<<','<<d_y<<')';
}

void position::lit(std::istream &ist)
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

std::istream &operator>>(std::istream &ist, position &p)
{
    p.lit(ist);
    return ist;
}

std::ostream &operator<<(std::ostream &ost, const position &p)
{
    p.affiche(ost);
    return ost;
}

position operator+(const position &p1, const position &p2)
{
    Position somme{p1.d_x+p2.d_x,p1.d_y+p2.d_y};
    return somme;
}

position &position::operator+=(const position &p)
{
    d_x+=p.d_x;
    d_y+=p.d_y;
    return *this;
}

position operator/(const position &p, double ratio)
{
    position division{p.d_x/ratio,p.d_y/ratio};
    return division;
}

position &position::operator/=(double r)
{
    d_x/=r;
    d_y/=r;
    return *this;
}

position operator*(double r, const position &p)
{
    position multiple{p.x()*r,p.y()*r};
    return multiple;
}
