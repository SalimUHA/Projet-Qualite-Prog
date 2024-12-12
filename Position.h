//
// Created by salim on 12/12/2024.
//

#ifndef POSITION_H
#define POSITION_H
#include <ostream>
#include <istream>


class Position{
public:
    Position(double x,double y);
    Position();
    double x() const;
    double y() const;
    void deplaceEn(double x, double y);
    void deplaceDe(double dx, double dy);
    double distance(const Position &p2) const;
    void affiche(std::ostream &ost) const;
    void lit(std::istream &ist);

    friend Position operator+(const Position &p1, const Position &p2);
    Position &operator+=(const Position &p);

    friend Position operator /(const Position &p, double r);
    Position &operator /=(double r);

    friend Position operator *(const double &r, const Position &p);
private:
    double d_x,d_y;
};

std::istream& operator>>(std::istream &ist, Position &p);
std::ostream& operator<<(std::ostream &ost, const Position &p);


#endif //POSITION_H
