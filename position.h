//
// Created by salim on 12/12/2024.
//

#ifndef POSITION_H
#define POSITION_H
#include <ostream>
#include <istream>


class position{
public:
    position(double x,double y);
    position();
    double x() const;
    double y() const;
    void deplaceEn(int x, int y);
    void deplaceDe(int dx, int dy);
    double distance(const position &p2) const;
    void affiche(std::ostream &ost) const;
    void lit(std::istream &ist);

    friend position operator+(const position &p1, const position &p2);
    position &operator+=(const position &p);

    friend position operator /(const position &p, double ratio);
    position &operator /=(double r);

    friend position operator *(const double &ratio, const position &p);
    friend position operator /(const position &p, double ratio);
    position &operator /=(double& ratio);

    friend position operator *(const double &r, const position &p);
private:
    double d_x,d_y;
};

std::istream& operator>>(std::istream &ist, position &p);
std::ostream& operator<<(std::ostream &ost, const position &p);


#endif //POSITION_H
