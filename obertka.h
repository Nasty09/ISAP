#include <iostream>
#include <tommath.h>
#ifndef OBERT_HPP
#define OBERT_HPP

mp_int p;

class mp
{
    mp_int a;
public:
    mp(const char *_a){mp_err err = mp_init(&a); mp_read_radix(&a, _a, 10);}
    mp(int _a){mp_err err = mp_init(&a); mp_set_l(&a, _a);}
    mp(mp_int _a) {mp_err err = mp_init_copy(&a,&_a);}
    mp() {mp_err err = mp_init(&a);}
    mp(const mp& other)
    { mp_err err = mp_init_copy(&a, &other.a); }
    ~mp(){mp_clear(&a);}

    mp& operator=(const mp& other)
    {
        mp_clear(&a);
        mp_err err = mp_init_copy(&a, &other.a);
        return *this;
    }
    mp operator* (mp b)
    {
        mp c;
        mp_err err;
        err = mp_mulmod(&this->a, &b.a, &p, &c.a);
        return c;
    }
    bool operator% (mp b)
    {
        mp c, d;
        mp_err err;
        err = mp_div(&this->a, &b.a, &c.a, &d.a);
        if (d == mp(0)) return 0;
        else return 1;
    }
    mp operator/ (mp b)
    {
        mp c, d;
        mp_err err;
        err = mp_div(&this->a, &b.a, &c.a, &d.a);
        return c;
    }
    mp operator+ (mp b)
    {
        mp c;
        mp_err err;
        err = mp_addmod(&this->a, &b.a, &p, &c.a);
        return c;
    }
    mp operator- (mp b)
    {
        mp c;
        mp_err err;
        err = mp_submod(&this->a, &b.a, &p, &c.a);
        return c;
    }
    bool operator== (mp b)
    {
        if (mp_cmp(&this->a, &b.a) == 0)
            return 1;
        return 0;
    }
    friend std::ostream& operator<< (std::ostream& out, const mp A)
    {
        int radix = 10;
        mp_fwrite(&A.a, radix, stdout);
        out << "";
        return out;
    }

    mp sqr_mod()
    {
        mp c;
        mp_err err;
        err = mp_sqrmod(&this->a, &p, &c.a);
        return c;
    }
    mp otr()
    {
        mp b;
        mp_neg(&this->a, &this->a);
        mp_mod(&this->a, &p, &b.a);
        return b;
    }
};
#endif
