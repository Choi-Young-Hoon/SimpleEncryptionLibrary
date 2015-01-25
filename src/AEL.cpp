/* ****************************************************************************
 *
 * Copyright 2013, 2014 informaticien77
 *
 * This file is part of Advanced Encryption Library.
 *
 * Advanced Encryption Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Advanced Encryption Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Advanced Encryption Library.  If not, see <http://www.gnu.org/licenses/>.
 *
 * 				AEL.cpp
 *
 * Author: informaticien77
 * Release date: 27th of June 2014
 *
 * ****************************************************************************
 */

#include "AEL.hpp"

//Number generator with specified bit-length
void ael::LargeInt::BitGenerator(unsigned int lenght){
    ael::LargeInt maxi(0x01), mini(0x0), un(0x01), result(0x0);

    for(unsigned int k = 0; k < lenght; k++){
        maxi.ToTheLeft();
    }
    mini = maxi;

    mini.ToTheRight();

    result.NumberGenerator(maxi, mini);

    *this = result;
}

//Fermat Primality Test
bool ael::LargeInt::FermatPrimality(void){
    ael::LargeInt bb(*this), un(1), p(bb), two(2), three(3), five(5), seven(7);
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
ael::LargeInt ael::LargeInt::EuclideAlgoPGCD(ael::LargeInt& b){
    ael::LargeInt reste(1), aa(*this), bb(b), zero(0), un(1);
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
bool ael::LargeInt::MillerRabinPrimality(unsigned int iterations){
    ael::LargeInt n1(*this), un(1), n2(0), s(0), d(0), a(0), c1(0), c2(0), r(0), s2(0), e(0), zero(0), plusa(0xFFFFF), deux(2), b(0), n0(n1);
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
        for(ael::LargeInt r(0); r < s; r += un){
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
