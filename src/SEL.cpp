/* ****************************************************************************
 *
 * MIT License
 *
 * Copyright (c) 2016 William Bonnaventure
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in a$
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * ****************************************************************************
 */

#include "SEL.hpp"

//Number generator with specified bit-length
void sel::LargeInt::BitGenerator(unsigned int lenght){
    sel::LargeInt maxi(1), mini(0), un(1), result(0);

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
        k = N.size_bits();
        aka = M.size_bits();
    }
    else{
        k = M.size_bits();
        aka = N.size_bits();
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
