#include <iostream>
#include <tommath.h>
#ifndef OBERT_HPP
#define OBERT_HPP

mp_int p;

class mp
{
    mp_int a;
public:
//    mp(const char *_a){mp_int c; mp_err err = mp_init(&c); err = mp_init(&a);mp_read_radix(&c, _a, 10); mp_init_copy(&a, &c); mp_clear(&c);}
//    mp(int _a){mp_int c; mp_err err = mp_init(&c); err = mp_init(&a);mp_set_l(&c, _a); mp_init_copy(&a, &c); mp_clear(&c);}
//    mp(mp_int _a) {mp_err err = mp_init(&a);mp_init_copy(&a,&_a);}
    mp(const char *_a){mp_err err = mp_init(&a); mp_read_radix(&a, _a, 10);}
    mp(int _a){mp_err err = mp_init(&a); mp_set_l(&a, _a);}
    mp(mp_int _a) {mp_err err = mp_init_copy(&a,&_a);}
    mp() {mp_err err = mp_init(&a);}
    ~mp(){}

    void set(int b){*this = mp(b);}
    void set(char b){*this = mp(b);}

    mp operator* (mp b)
    {
        mp c;
        mp_err err;
        err = mp_mulmod(&b.a, &this->a, &p, &c.a);
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
    mp sqrt()
    {
        mp c;
        mp_err err;
        err = mp_sqrt(&this->a, &c.a);
        return c;
    }
    mp otr() { mp b; mp_neg(&this->a, &this->a); mp_mod(&this->a, &b.a, &p); return b; }
};
#endif
