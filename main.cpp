#include <iostream>
#include <tommath.h>
#include "obertka.h"
#include "jacobi.h"

int main()
{
    mp_init(&p);
    mp_read_radix(&p, "115792089237316195423570985008687907853269984665640564039457584007913129639319", 10);
    alph= "87789765485885808793369751294406841171614589925193456909855962166505018127157";
//    //point Q(set(1), 2, 1, int_sqrt(5)), P1(1, int_sqrt(3), 0, 2);
    mp k1 = 6, k2 = 7, k3 = 13,
            q = "28948022309329048855892746252171976963338560298092253442512153408785530358887",
            x = "65987350182584560790308640619586834712105545126269759365406768962453298326056",
            y = "22855189202984962870421402504110399293152235382908105741749987405721320435292",
            z = 1, l=mp(1)+koef.otr();//,t = koef * z.sqr_mod().sqr_mod(); //t = x.sqr_mod();
    koef = mp(1)+l.otr();
    //point P(x * t, y * t, z, t), Q1, Q2, Q3, Q4, Q5;
    point P(mp(2).otr()*(x+z)*y, l*(x.sqr_mod() + z.sqr_mod() + mp(2)*x*z).otr()+y.sqr_mod(),
            l*(x.sqr_mod() + z.sqr_mod() + mp(2)*x*z)+y.sqr_mod(),l*z.sqr_mod() + y.sqr_mod() + mp(2)*x*z + (mp(2)+l.otr())*x.sqr_mod()),
            Q1, Q2, Q3, Q4, Q5;
    std::cout << P.in() << "\n" << P << "\n";
    Q1 = P.crat(k1);
    std::cout << Q1.in() << "\n";
    std::cout << koef << "\n";
//    Q2 = P.crat(k2);

//    //q = p + p.sqrt() * 2 + 1;
//    Q3 = P.crat(q);
//    //std::cout << (point() == Q4) << "\n";
//    //std::cout << Q3 << "\n";

//    Q4 = Q1 + Q1;
//    std::cout << Q4 << "\n";
//    Q5 = P.crat(k3);



//    std::cout << (Q4 == Q5) << "\n";
    mp_clear(&p);
    return 0;
}
