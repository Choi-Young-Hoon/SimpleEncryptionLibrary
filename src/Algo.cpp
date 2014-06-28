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
 * 				Algo.cpp
 *
 * Author: informaticien77
 * Release date: 28th of June 2014
 *
 * ****************************************************************************
 */

#include "AEL.hpp"

//Number generator with specified bit-length
ael::LargeInt ael::Algo::BitGenerator(unsigned int lenght){
    ael::LargeInt maxi(0x01), mini(0x0), un(0x01), result(0x0);

    for(unsigned int k = 0; k < lenght; k++){
        maxi.Decalage_Gauche();
    }
    mini = maxi;
    
    mini.Decalage_Droite();
    
    result.NumberGenerator(maxi, mini);

    return result;
}

//Fermat Primality Test
bool ael::Algo::FermatPrimality(ael::LargeInt& b){
    ael::LargeInt bb(b), un(1), p(bb), deux(2), trois(3), cinq(5), sept(7);
    p -= un;

    deux.Modular_Exp(p, bb);
    if(deux != un){
        return false;
    }

    trois.Modular_Exp(p, bb);
    if(trois != un){
        return false;
    }

    cinq.Modular_Exp(p, bb);
    if(cinq != un){
        return false;
    }

    sept.Modular_Exp(p, bb);
    if(sept != un){
        return false;
    }

    return true;
}

//Euclide Algorithm to calculate PGCD
ael::LargeInt ael::Algo::EuclideAlgoPGCD(ael::LargeInt& a, ael::LargeInt& b){
    ael::LargeInt reste(1), aa(a), bb(b), zero(0), un(1);
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
bool ael::Algo::MillerRabinPrimality(ael::LargeInt& n0, unsigned int iterations){
    ael::LargeInt n1(n0), un(1), n2(0), s(0), d(0), a(0), c1(0), c2(0), r(0), s2(0), e(0), zero(0), plusa(0xFFFFF), deux(2), b(0);
    bool status = false;
    n1 -= un;
    n2 = n1;

    while(((n2.GetFirst() & 0x01) == 0) && (n2 != zero)){
        s += un;
        n2.Decalage_Droite();
    }

    if(s == zero){
        return false;
    }

    d = n2;
    s2 = s;
    s2 -= un;

    a.Generer(1); //Nombre aléatoire
    //a = un;
    //a += un;

    for(unsigned int k = 0; k < iterations; k += 1){
        a *= plusa;
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

        a.Show();
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
            e.Decalage_Gauche();
            
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