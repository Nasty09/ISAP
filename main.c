#include <stdio.h>
#include <tommath.h>

mp_int set(int a)
{
    mp_int _a;
    mp_set(&_a, a);
    return _a;
}

mp_int int_mul_2(const mp_int a, const mp_int b)
{
    mp_int c;

    mp_err f = mp_mul(&a, &b, &c);
    if (f == 0) return c;
    else return set(f);
}

mp_int int_mul_4(const mp_int a, const mp_int b, const mp_int c, const mp_int d)
{
    mp_int e;
    mp_err f;
    f = mp_mul(&a, &b, &e);
    f = mp_mul(&e, &c, &e);
    f = mp_mul(&e, &d, &e);
    return e;
}

mp_int int_mul_2d(const int b, const mp_int a)
{
    mp_int c;
    mp_err f;
    f = mp_mul_2d(&a, b, &c);
    return c;
}

int int_mod_2d(const mp_int a, int b)
{
    mp_int k;
    mp_err f;
    f = mp_mod_2d(&a, b, &k);
    if (mp_cmp(&k, 0)) return 0;
    else return 1;
}

mp_int int_add(const mp_int a, const mp_int b)
{
    mp_int c;
    mp_err f;
    f = mp_add(&a, &b, &c);
    return c;
}

mp_int int_sub(const mp_int a, const mp_int b)
{
    mp_int c;
    mp_err f;
    f = mp_sub(&a, &b, &c);
    return c;
}

mp_int int_sqr(const mp_int a)
{
    mp_int c;
    mp_err f;
    f = mp_sqr(&a, &c);
    return c;
}

int int_eq(const mp_int a, const mp_int b)
{
    if (mp_cmp(&a, &b) == 0) return 1;
    else return 0;
}

mp_int int_sqrt(const mp_int *A)
{
    mp_int *c;
    mp_err f;
    f = mp_sqrt(A, c);
    return *c;
}

typedef struct
{
    mp_int _x, _y, _z, _t;
}point;

point *New_point_empty ()
{
    point *A;
    A->_x = set(0);
    A->_y = set(1);
    A->_z = set(1);
    A->_t = set(1);
    return A;
}

point *New_point (mp_int x, mp_int y, mp_int z, mp_int t)
{
    point *A;
    A->_x = x;
    A->_y = y;
    A->_z = z;
    A->_t = t;
    return A;
}

int point_eq (const point *A, const point *B) { return int_eq(B->_x, A->_x) && int_eq(B->_y, A->_y) && int_eq(B->_z, A->_z) && int_eq(B->_t, A->_t); }

void point_out (const point *A)
{
    char out[1000];
    int radix = 10;
    FILE stream;
    mp_err f;
    fwrite("(", 1, 1000, &stream);
    f = mp_fwrite(&A->_x, radix, &stream);
    fwrite(",", 1, 1000, &stream);
    f = mp_fwrite(&A->_y, radix, &stream);
    fwrite(",", 1, 1000, &stream);
    f = mp_fwrite(&A->_z, radix, &stream);
    fwrite(",", 1, 1000, &stream);
    f = mp_fwrite(&A->_t, radix, &stream);
    fwrite(")\n", 1, 1000, &stream);
    fread(&out, 1, 1000, &stream);
    printf("%s/n",out);
}

int point_in(mp_int a, point *P)
{

    return int_eq(int_sub(int_add(int_mul_2(P->_x, P->_x), int_mul_2(P->_y, P->_y)), int_mul_2(P->_t, P->_t)), set(0)) &&
        int_eq(int_sub(int_add(int_mul_2(a, int_mul_2(P->_x, P->_x)), int_mul_2(P->_z, P->_z)), int_mul_2(P->_t, P->_t)), set(0));
}

point *point_neg(point *A) { mp_err f; f = mp_neg(&A->_x, &A->_x); return A; }

point *point_sum (const point *P, const point *B, const mp_int a)
{
    point *C;
    if (B == P)
    {

        C->_x = int_mul_4(int_mul_2d(1, P->_x), P->_y, P->_z, P->_t);
        C->_y = int_sub(int_mul_2(int_sqr(P->_y), int_sqr(P->_t)), int_mul_2(int_sqr(P->_x), int_sqr(P->_z)));
        C->_z = int_sub(int_mul_2(int_sqr(P->_z), int_sqr(P->_t)), int_mul_2(int_mul_2(a, int_sqr(P->_x)), int_sqr(P->_y)));
        C->_t = int_add(int_mul_2(int_sqr(P->_z), int_sqr(P->_x)), int_mul_2(int_sqr(P->_t), int_sqr(P->_y)));
    }
    else
    {
        C->_x = int_add(int_mul_4(P->_x, B->_y, B->_z, P->_t), int_mul_4(B->_x, P->_y, P->_z, B->_t));
        C->_y = int_sub(int_mul_4(P->_y, B->_y, B->_t, P->_t), int_mul_4(B->_x, P->_x, P->_z, B->_z));
        C->_z = int_sub(int_mul_4(P->_z, B->_z, B->_t, P->_t), int_mul_2(int_mul_4(a, B->_x, P->_x, P->_y), B->_y));
        C->_t = int_add(int_mul_4(P->_t, B->_y, P->_t, B->_y), int_mul_4(P->_z, B->_x, P->_z, B->_x));
    }
    return C;
}

point *crat(mp_int k, mp_int a, point *B)
{
    point *Q, *P = B;
    mp_err f;
    int n = 0;
    int buf[n];
    while (mp_cmp(&k, 0) == 1)
    {
        buf[n] = int_mod_2d(k, 1);
        f = mp_div_2(&k, &k);
        n += 1;
    }
    for (int i = n - 1; i >= 0; i--)
    {
        Q = point_sum(Q, Q, a);
        if (buf[i] == 1) Q = point_sum(P, Q, a);
    }
    /*for (int i = n - 1; i >= 0; i--)
    {
        if (f[i] == 0)
        {
            P = P.point_sum(Q, a);
            Q = Q.point_sum(Q, a);
        }
        if (f[i] == 1)
        {
            Q = Q.point_sum(P, a);
            P = P.point_sum(P, a);
        }
    }*/
    printf("%d/n",point_in(a, Q));
    return Q;
}


int main()
{
    mp_int alph;
    mp_set(&alph, 1);
    //point Q(set(1), 2, 1, sqrt(5)), P1(1, sqrt(3), 0, 2);
    point *P = New_point(set(0), set(2), set(-2), set(2)), *Q1 = New_point_empty(), *Q2 = New_point_empty(), *Q4 = New_point_empty(),
            *Q5 = New_point_empty(), *Q = New_point_empty();
    mp_int k1 = set(2), k2 = set(8), k3 = set(10), p = set(2), q;

    printf("%d/n",point_in(alph, P));
    Q1 = crat(k1, alph, P);
    Q2 = crat(k2, alph, P);

    q = int_sqrt(&p);
    q = int_add(int_add(p, int_mul_2d(1,q)), set(1));
    Q4 = crat(int_sub(p, set(1)), alph, P);
    printf("%d/n",point_eq(Q, Q4));
    point_out(Q4);

    for (int i = 1; i <= 12; i++)
    {
        Q5 = point_sum(P, Q5, alph);
    }

    point_out(point_sum(Q1, Q2, alph));
    point_out(crat(k3, alph, P));
    point_out(Q5);
    return 0;
}
