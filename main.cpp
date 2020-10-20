#include <iostream>
#include <tommath.h>

class mp
{
    mp_int a;
public:
    mp(int _a){mp_err err = mp_init(&a); mp_set(&a, _a);}
    mp() {mp_err err = mp_init(&a);};
    mp_int get_a() {return a;}
    ~mp(){mp_clear(&a);}

    mp operator* (mp b)
    {
        mp c;
        mp_err err;
        err = mp_mul(&b.a, &this->a, &c.a);
        return c;
    }
    bool operator% (int b)
    {
        mp c;
        mp_err err;
        err = mp_mod_2d(&this->a, b, &c.a);
        if (c == mp(0)) return 0;
        else return 1;
    }
    mp operator/ (int b)
    {
        mp c, d;
        mp_err err;
        err = mp_div_2d(&this->a, b, &c.a, &d.a);
        return c;
    }
    mp operator+ (mp b)
    {
        mp c;
        mp_err err;
        err = mp_add(&this->a, &b.a, &c.a);
        return c;
    }
    mp operator- (mp b)
    {
        mp c;
        mp_err err;
        err = mp_sub(&this->a, &b.a, &c.a);
        return c;
    }
    bool operator== (mp b)
    {
        if (mp_cmp(&this->a, &b.a) == 0)
            return 1;
        return 0;
    }
    friend std::ofstream& operator<< (std::ostream& out, mp A)
    {
        FILE stream;
        int radix = 10;
        mp_fwrite(&A.a, radix, &stream);
        fread(&out, 1, 1000, &stream);
        return out;
    }
    mp sqr()
    {
        mp c;
        mp_err err;
        err = mp_sqr(&this->a, &c.a);
        return c;
    }
    mp sqrt()
    {
        mp c;
        mp_err err;
        err = mp_sqrt(&this->a, &c.a);
        return c;
    }
    mp otr() { mp_neg(&a, &a); return *this; }
};

//std::ostream& operator<< (std::ostream& out, mp_int A)
//{


//    FILE stream;
//    mp_fwrite(&A, radix, &stream);
//    fread(&out, 1, 1000, &stream);
//    return out;
//}

class point
{
    mp _x, _y, _z, _t;
public:
    point(mp x = 0, mp y = 1, mp z = 1, mp t = 1) : _x(x), _y(y), _z(z), _t(t) {};

    mp get_x() { return _x; }
    mp get_y() { return _y; }
    mp get_z() { return _z; }
    mp get_t() { return _t; }

    bool operator== (const point& A) { return _x == A._x && _y == A._y && _z == A._z && _t == A._t; }
    bool operator!= (const point& A) { return !(*this == A); }
    friend std::ostream& operator<< (std::ostream& out, point A)
    {
        int radix = 10;
        mp_err err;
        out << "(" << A._x << ", " << A._y << ", " << A._z << ", " << A._t << ")\n";
        return out;
    }

    bool in(mp a)
    {

        return _x.sqr() + _y.sqr() - _t.sqr() == mp(0) &&
            a * _x.sqr() + _z.sqr() - _t.sqr() == mp(0);
    }

    point otr() { _x.otr(); return *this; }

    point sum (point& A, mp a)
    {
        if (*this == A)
        {
            return point(_x * _y * _z * _t * mp(2),
                _y.sqr() * _t.sqr() - _x.sqr() * _z.sqr(),
                _z.sqr() * _t.sqr() - a * _x.sqr() * _y.sqr(),
                _z.sqr() * _x.sqr() + _t.sqr() * _y.sqr());
        }
        else
        {
            return point(_x * A._y * A._z * _t + A._x * _y * _z * A._t,
                _y * A._y * A._t * _t - A._x * _x * _z * A._z,
                _z * A._z * A._t * _t - a * A._x * _x * _y * A._y,
                _t * A._y * _t * A._y + _z * A._x * _z * A._x);
        }
    }

    point crat(mp k, mp a)
    {
        point Q, P = *this;
        int n = 0;
        bool buf[100];
        mp zero(0);
        while (!(k == zero))
        {
            buf[n] = k % 1;
            k = k / 1;
            ++n;
        }
        for (int i = n - 1; i >= 0; i--)
        {
            Q = Q.sum(Q, a);
            if (buf[i] == 1) Q = Q.sum(P, a);
        }
        /*for (int i = n - 1; i >= 0; i--)
        {
            if (f[i] == 0)
            {
                P = P.sum(Q, a);
                Q = Q.sum(Q, a);
            }
            if (f[i] == 1)
            {
                Q = Q.sum(P, a);
                P = P.sum(P, a);
            }
        }*/
        std::cout << Q.in(a) << "\n";
        return Q;
    }
};


int main()
{
    mp alph(1);
    //point Q(set(1), 2, 1, int_sqrt(5)), P1(1, int_sqrt(3), 0, 2);
    point P(0, 2, -2, 2), Q1, Q2, Q4, Q5;
    mp k1 = 2, k2 = 8, k3 = 10, p = 2, q;

    std::cout << P.in(alph);
    Q1 = P.crat(k1, alph);
    Q2 = P.crat(k2, alph);

    q = p + p.sqrt() * 2 + 1;
    Q4 = P.crat(p - mp(1), alph);
    std::cout << (point() == Q4) << "\n";
    std::cout << Q4 << "\n";

    for (int i = 1; i <= 12; i++)
    {
        Q5 = Q5.sum(P, alph);
    }

    std::cout << Q1.sum(Q2, alph) << "\n" << P.crat(k3, alph) << " " << Q5 << "\n";
    return 0;
}

