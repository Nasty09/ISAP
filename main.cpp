#include <iostream>
#include <tommath.h>
#include "obertka.h"
#include "jacobi.h"

int main()
{
    mp_init(&p);
    mp_read_radix(&p, "115792089237316195423570985008687907853269984665640564039457584007913111864739", 10);
    koef = "115792089237316195423570985008687907853269984665640564039457584007913111864737";
    mp      q = "4824670384888174809315457708695329493868526062531865828358260708486391273721",
            x = "86773867670483746082709700497332781598034016226947998080571074369332058445893",
            y = "112365783073842736181650671369471258524588261898469739668735228897200995462257",
            z = "53269948314907700562817814682691121416875131851387647397949804668930162464909",
            t = "34969497036250894576602400300903320615522974325083826128152497107656115683806",
            k1 = mp(3)*q/mp(4321), k2 = mp(4)*q/mp(12345), k3 = k1+k2;

    point P(x,y,z,t),Q1, Q2, Q3, Q4, Q5, Pneg(x,y,z,t);
    Pneg.otr();
    std::cout <<"k1: "<<k1<<"\nk2: "<<k2<<"\nk3: "<<k3<<"\ntochka P: \n"<<P<<"\n\n";

    std::cout <<"proverka na prinadleznost tocki P: " << P.in() << "\n\n";

    Q1 = P.crat(k1);
    std::cout << "proverka na prinadleznost tochki kratnosti k1: "<<Q1.in() << "\n\n";
    Q2 = P.crat(k2);

    Q3 = P.crat(mp(4)*q);
    std::cout << "tochka kratnosti 4q:\n"<<Q3<< "\nneitralnaya: \n" << point() << "\n\n";

    Q3 = P.crat(mp(4)*q-1);
    std::cout << "proverka na ravenstvo tochki kratnosti 4q-1 i -P: "<< (Pneg.from_pol_to() == Q3.from_pol_to()) << "\n";
    std::cout << "tochka kratnosti 4q-1:\n" << Q3 << "\n-P: \n" << Pneg << "\n\n";

    Q3 = P.crat(mp(4)*q+1);
    std::cout << "proverka na ravenstvo tochki kratnosti 4q+1 i P: " << (P.from_pol_to() == Q3.from_pol_to()) << "\n";
    std::cout << "tochka kratnosti 4q+1:\n"<<Q3 << "\nP: \n"<<P<<"\n\n";

    Q4 = Q2 + Q1;
    std::cout << "proverka na prinadleznost summi tochek kratnosti k1 i k2: " << Q4.in() << "\n";
    std::cout << "summa tochek kratnosti k1 i k2:\n" << Q4 << "\n";
    Q5 = P.crat(k3);
    std::cout << "tochka kratnosti k3:\n"<<Q5<<"\n";
    std::cout << "proverka na ravenstvo summi tochek kratnosti k1 i k2 i tochki kratnosti k3: "<<(Q4.from_pol_to() == Q5.from_pol_to()) << "\n\n";
    mp_clear(&p);
    return 0;
}
