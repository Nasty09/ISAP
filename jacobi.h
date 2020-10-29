#include <iostream>
#include <tommath.h>
#include "obertka.h"
#ifndef JACOBI_HPP
#define JACOBI_HPP

mp koef;

class point
{
    mp _x, _y, _z, _t;
public:
    point(mp x = 0, mp y = 1, mp z = 1, mp t = 1) : _x(x), _y(y), _z(z), _t(t) {};
    ~point(){};

    mp get_x() { return _x; }
    mp get_y() { return _y; }
    mp get_z() { return _z; }
    mp get_t() { return _t; }

    bool operator== (const point& A) { return _x == A._x && _y == A._y && _z == A._z && _t == A._t; }
    bool operator!= (const point& A) { return !(*this == A); }
    friend std::ostream& operator<< (std::ostream& out, point A)
    {
        out << "(" << A._x << ", \n" << A._y << ", \n" << A._z << ", \n" << A._t << ")\n";
        return out;
    }

    bool in()
    {
        return _x.sqr_mod() + _y.sqr_mod() == _t.sqr_mod() &&
            koef * _x.sqr_mod() + _z.sqr_mod() == _t.sqr_mod();
    }

    point otr() { _x=_x.otr(); return *this; }

    point operator+ (point &A)
    {
        if (*this == A)
        {
            return point(_x * _y * _z * _t * mp(2),
                (_y * _t).sqr_mod() - (_z * _t).sqr_mod() + (_y * _z).sqr_mod(),
                (_z * _t).sqr_mod() - (_y * _t).sqr_mod() + (_y * _z).sqr_mod(),
                (_z * _t).sqr_mod() + (_y * _t).sqr_mod() - (_y * _z).sqr_mod());
        }
        else
        {
            return point(_x * A._y * A._z * _t + A._x * _y * _z * A._t,
                _y * A._y * A._t * _t - A._x * _x * _z * A._z,
                _z * A._z * A._t * _t - koef * A._x * _x * _y * A._y,
                (_t * A._y).sqr_mod() + (_z * A._x).sqr_mod());
        }
    }

    point crat(mp k)
    {
        point Q, P = *this;
        int n = 0;
        bool buf[257];
        mp zero(0);
        while (!(k == zero))
        {
            buf[n] = k % mp(2);
            k = k / mp(2);
            ++n;
        }
        buf[n]=0;
        n++;
        for (int i = n - 1; i >= 0; i--)
        {
            if (buf[i] == 0)
            {
                P = P + Q;
                Q = Q + Q;
            }
            if (buf[i] == 1)
            {
                Q = Q + P;
                P = P + P;
            }
        }
        return Q;
    }
};
#endif
