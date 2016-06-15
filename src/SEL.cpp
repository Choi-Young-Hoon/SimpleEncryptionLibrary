/* ****************************************************************************
 *
 * Copyright 2013-2016 informaticien77
 *
 * This file is part of Simple Encryption Library.
 *
 * Simple Encryption Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Simple Encryption Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Simple Encryption Library.  If not, see <http://www.gnu.org/licenses/>.
 *
 * 				SEL.cpp
 *
 * Author: informaticien77
 * Release date: 27th of June 2014
 *
 * ****************************************************************************
 */

#include "SEL.hpp"

//Number generator with specified bit-length
void sel::LargeInt::BitGenerator(unsigned int lenght){
    sel::LargeInt maxi(0x01), mini(0x0), un(0x01), result(0x0);

    for(unsigned int k = 0; k < lenght; k++){
        maxi.ToTheLeft();
    }
    mini = maxi;

    mini.ToTheRight();

    result.NumberGenerator(maxi, mini);

    *this = result;
}

//Fermat Primality Test
bool sel::LargeInt::FermatPrimality(void){
    sel::LargeInt bb(*this), un(1), p(bb), two(2), three(3), five(5), seven(7);
    p -= un;

    two.Modular_Exp(p, bb);
    if(two != un){
        return false;
    }

    three.Modular_Exp(p, bb);
    if(three != un){
        return false;
    }

    five.Modular_Exp(p, bb);
    if(five != un){
        return false;
    }

    seven.Modular_Exp(p, bb);
    if(seven != un){
        return false;
    }

    return true;
}

//Euclide Algorithm to calculate PGCD
sel::LargeInt sel::LargeInt::EuclideAlgoPGCD(sel::LargeInt& b){
    sel::LargeInt reste(1), aa(*this), bb(b), zero(0), un(1);
    while(reste != zero){
        reste = aa;
        reste %= bb;

        if(reste == zero){
            break;
        }
        else{
            aa = bb;
            bb = reste;
        }

    }
    return bb;
}

//Miller-Rabin Primality Test
bool sel::LargeInt::MillerRabinPrimality(unsigned int iterations){
    sel::LargeInt n1(*this), un(1), n2(0), s(0), d(0), a(0), c1(0), c2(0), r(0), s2(0), e(0), zero(0), plusa(0xFFFFF), deux(2), b(0), n0(n1);
    bool status = false;
    n1 -= un;
    n2 = n1;

    while(((n2.GetFirst() & 0x01) == 0) && (n2 != zero)){
        s += un;
        n2.ToTheRight();
    }

    if(s == zero){
        return false;
    }

    d = n2;
    s2 = s;
    s2 -= un;

    a.Generate(1); //Nombre aléatoire

    for(unsigned int k = 0; k < iterations; k += 1){
        a *= a; //a *= plusa
        a %= n0;
        a += deux;
        //a %= n0;

        /*while(EuclideAlgoPGCD(a, n0) != un){
            a *= plusa;
            a %= n0;
            a += deux;
            a %= n0;
            //plusa += 3;
        }*/

        //a.Show();
        c1 = a;
        c1.Modular_Exp(d, n0);

        if(c1 == un){
            status = true;
            break;
        }
        else{
            status = false;
        }

        e = d;
        for(sel::LargeInt r(0); r < s; r += un){
            c2 = a;
            e.ToTheLeft();

            c2.Modular_Exp(e, n0);

            if(c2 == n1){
                status = true;
                break;
            }
        }

        if(status == true){
            break;
        }
    }
    return status;
}

sel::LargeInt sel::Karatsuba(sel::LargeInt& N, sel::LargeInt& M){
    unsigned int k = 0, aka = 0;

    if (N < M){
        k = N.size();
        aka = M.size();
    }
    else{
        k = M.size();
        aka = N.size();
    }

    sel::LargeInt a(0), b(0), c(0), d(0), P1(0), P2(0), P3(0), A(0), B(0), S(0), zero(0), S1(0), S2(0), atemp(0), ctemp(0);

    if ((k == 0) || (N == zero) || (M == zero)){
        return(S);
    }
    else if(aka <= 16){
        sel::LargeInt result(N.GetFirst()*M.GetFirst());
        //result = N;
        //result *= M;
        return(result);
    }

    a = N;
    for (unsigned int i = 0; i < (k/2); i++){
        a.ToTheRight();
    }
    b = N;
    atemp = a;
    for (unsigned int i = 0; i < (k/2); i++){
        atemp.ToTheLeft();
    }
    b -= atemp;

    c = M;
    for (unsigned int i = 0; i < (k/2); i++){
        c.ToTheRight();
    }
    d = M;
    ctemp = c;
    for (unsigned int i = 0; i < (k/2); i++){
        ctemp.ToTheLeft();
    }
    d -= ctemp;

    if((a == zero) || (c == zero)){
        P1 = zero;
    }
    else{
        P1 = sel::Karatsuba(a,c);
    }

    if((b == zero) || (d == zero)){
        P2 = zero;
    }
    else{
        P2 = sel::Karatsuba(b,d);
    }

    int factor = -1;

    if(a >= b){
        S1 = a;
        S1 -= b;
        if(c > d){
            S2 = c;
            S2 -= d;
            P3 = sel::Karatsuba(S1,S2);
            factor = -1;
        }
        else if(c == d){
            S2 = zero;
            P3 = zero;
            factor = 0;
        }
        else{
            S2 = d;
            S2 -= c;
            P3 = sel::Karatsuba(S1,S2);
            factor = 1;
        }
    }
    else{
        S1 = b;
        S1 -= a;
        if(c >= d){
            S2 = c;
            S2 -= d;
            P3 = sel::Karatsuba(S1,S2);
            factor = 1;
        }
        else if(c == d){
            S2 = zero;
            P3 = zero;
            factor = 0;
        }
        else{
            S2 = d;
            S2 -= c;
            P3 = sel::Karatsuba(S1,S2);
            factor = -1;
        }
    }

    A = P1;

    for (unsigned int i = 0; i < 2*(k/2); i++){
        A.ToTheLeft();
    }

    B = P1;
    B += P2;

    if(factor < 0){
        B -= P3;
    }
    else if(factor > 0){
        B += P3;
    }

    for (unsigned int j = 0; j < (k/2); j++){
        B.ToTheLeft();
    }

    S = A;
    S += B;
    S += P2;

    return(S);
}
