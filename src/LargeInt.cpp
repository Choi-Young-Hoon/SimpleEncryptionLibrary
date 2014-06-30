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
 * 				LargeInt.cpp
 *
 * Author: informaticien77
 * Release date: 27th of June 2014
 *
 * ****************************************************************************
 */

#include "AEL.hpp"

//Constructor
ael::LargeInt::LargeInt(){
    nombre.resize(0);
    nombre.clear();
}

//String to LargeInt
ael::LargeInt::LargeInt(unsigned char a[], unsigned int size){
    unsigned int taille = ceil(size / 4.0), h = 0;
    nombre.resize(taille);
    for(unsigned int i = 0; i < taille; i++){
        nombre[i] = 0;
		for(unsigned int j = 0; j < 4; j++){
			h = i*4 + j;
			if(h < size){
				h = a[i*4+j];
				h <<= (j*8);
				nombre[i] += h;
			}
		}
    }
}

//Copy from another LargeInt
ael::LargeInt::LargeInt(LargeInt const& a){
    nombre.resize(a.nombre.size());
    for(unsigned int i = 0; i < a.nombre.size(); i++){
        nombre[i] = a.nombre[i];
    }
}

//Put a value to the first array of the LargeInt
ael::LargeInt::LargeInt(unsigned int a){
    nombre.resize(1);
    nombre[0] = a;
}

//Destructor
ael::LargeInt::~LargeInt(){

}

//Show the LargeInt value in the console
const void ael::LargeInt::Show(){
    for(int i = nombre.size() - 1; i >= 0; i--){
        std::cout << std::hex << nombre[i] << " ";
    }
    std::cout << std::endl;
}

//Move to the right all the bits of the LargeInt
void ael::LargeInt::ToTheRight(){
    unsigned int buffer = 0;
    for(signed int i = (nombre.size() - 1); i >= 0; i--){
        if((nombre[i]&1)>0){
            nombre[i]>>=1;
            nombre[i]+= (buffer*0x80000000);
            buffer = 1;
        }
        else{
            nombre[i]>>=1;
            nombre[i]+= (buffer*0x80000000);
            buffer = 0;
        }
    }
    if(nombre[nombre.size()-1] == 0 ){
        if(nombre.size() > 1){
            nombre.pop_back();
        }
    }
}

//Move to the left all the bits of the LargeInt
void ael::LargeInt::ToTheLeft(){
    unsigned int buffer = 0;
    for(unsigned int i = 0; i < nombre.size(); i++){
        if((nombre[i]&0x80000000)>0){
            nombre[i]<<=1;
            nombre[i]+=buffer;
            buffer = 1;
        }
        else{
            nombre[i]<<=1;
            nombre[i]+=buffer;
            buffer = 0;
        }
    }
    if(buffer != 0){
        nombre.push_back(buffer);
    }
}

//Generate a pseudo-random number
//This function have to be more close of a random number in the future
void ael::LargeInt::Generer(unsigned int taille){
    nombre.resize(taille);
    std::srand(time(NULL));

    for(unsigned int i = 0; i < nombre.size(); i++){
        nombre[i] = (std::rand()*std::rand()) % 0x100000000;
    }

    nombre[0] = (nombre[0] & 0xFFFFFFFB);

    if((nombre[0] & 0x01) == 0){
        nombre[0] = (nombre[0] | 0x01);
    }

}

//Generate a pseudo-random number include between two limits
//Also this function will be improve
void ael::LargeInt::NumberGenerator(LargeInt& maxi, LargeInt& mini){
    unsigned int integerlenght = 0, extrasize = 1, filter = 0, random = 0;
    bool start = true;
    srand(time(NULL));

    if(maxi.nombre.size() == mini.nombre.size()){
        integerlenght = maxi.nombre.size();
    }
    else{
        integerlenght = ((rand()) % (maxi.nombre.size() - mini.nombre.size())) + mini.nombre.size();
    }
    nombre.resize(integerlenght);

    //if(maxi.nombre[maxi.nombre.size()-1] > 0x)
    while(extrasize < maxi.nombre[maxi.nombre.size()-1]){
        extrasize <<= 1;
        if(extrasize == 0){
            //extrasize = 0xFFFFFFFF;
            break;
        }
    }

    if((extrasize == 0) || (maxi.nombre[maxi.nombre.size()-1] == 1)){
        filter = 0xFFFFFFFF;
    }
    else{
        filter = (extrasize - 1);
    }
    random = (rand()*rand()) % 0x100000000;

    while((*this < mini) || (*this > maxi) || (start)){

        for(unsigned int k = 0; k < integerlenght; k++){
            random = (rand()*random) % 0x100000000;
            //random <<= 1;
            nombre[k] = (random + rand()) % 0x100000000;
        }

        nombre[nombre.size()-1] = (nombre[nombre.size()-1] & filter);

        while((nombre[nombre.size()-1] < mini.nombre[mini.nombre.size()-1]) && (nombre.size() == mini.nombre.size())){
            nombre[nombre.size()-1] <<= 1;
            nombre[nombre.size()-1] += (rand() % 0x100);
        }

        if((maxi.nombre.size() == mini.nombre.size()) && (maxi.nombre.size() == integerlenght)){
            nombre[nombre.size()-1] = (((nombre[nombre.size()-1]*nombre[nombre.size()-1]) % (maxi.nombre[maxi.nombre.size()-1] - mini.nombre[mini.nombre.size()-1])) + mini.nombre[mini.nombre.size()-1]);
        }

        if((nombre[nombre.size()-1] == 0) && (nombre.size() > 1)){
            nombre.pop_back();
        }

        if(start){
            start = false;
        }
    }
    nombre[0] = (nombre[0] | 0x1);
}

//Get the fisrt array of the vector number.
unsigned int ael::LargeInt::GetFirst(){
    return nombre[0];
}

//Is equal operator
bool ael::LargeInt::operator==(LargeInt const& a){
    if(nombre == a.nombre){
        return true;
    }
    else{
        return false;
    }
}

//Isn't equal operator
bool ael::LargeInt::operator!=(LargeInt const& a){
    return !(*this == a);
}

//Inferior operator
bool ael::LargeInt::operator<(LargeInt const& a){
    bool state = false;
    if(nombre.size() < a.nombre.size()){
        return true;
    }
    else if(nombre.size() > a.nombre.size()){
        return false;
    }
    else if(nombre == a.nombre){
        return false;
    }
    else{
        for(int long long i = (nombre.size() - 1); i >= 0; i--){
            if(nombre[i] < a.nombre[i]){
                state = true;
                break;
            }
            else if(nombre[i] > a.nombre[i]){
                state = false;
                break;
            }
        }
        return state;
    }
}

//Inferior or equal operator
bool ael::LargeInt::operator<=(LargeInt const& a){
    if(*this < a){
        return true;
    }
    else if(*this == a){
        return true;
    }
    else{
        return false;
    }
}

//Superior operator
bool ael::LargeInt::operator>(LargeInt const& a){
    if(*this <= a){
        return false;
    }
    else{
        return true;
    }
}

//Superior or equal operator
bool ael::LargeInt::operator>=(LargeInt const& a){
    if(*this < a){
        return false;
    }
    else{
        return true;
    }
}

//Equal operator
ael::LargeInt& ael::LargeInt::operator=(LargeInt const& a){
    nombre.resize(a.nombre.size());

    for(unsigned int long long i = 0; i < a.nombre.size(); i++){
        nombre[i] = a.nombre[i];
    }

    return *this;
}

//Assignment by sum
void ael::LargeInt::operator+=(LargeInt const& a){
    unsigned int long long buffer = 0, memento = 0;
    unsigned int diff = 0, quit = 0, i = 0;
    std::vector<unsigned int> b(0);

    while(quit == 0){
        if(i >= nombre.size()){
            if(i < a.nombre.size()){
                buffer = static_cast<unsigned int long long>(a.nombre[i]) + memento;
                if(buffer > 0xFFFFFFFF){
                    b.push_back(static_cast<unsigned int>(buffer & 0xFFFFFFFF));
                    memento = buffer;
                    memento >>= 32;
                }
                else{
                    b.push_back(static_cast<unsigned int>(buffer));
                    memento = 0;
                }
            }
            else{
                if(memento != 0){
                    b.push_back(static_cast<unsigned int>(memento));
                }
                quit = 1;
            }
        }
        else{
            if(i < a.nombre.size()){
                buffer = (static_cast<unsigned int long long>(nombre[i]) + static_cast<unsigned int long long>(a.nombre[i]) + memento);
                if(buffer > 0xFFFFFFFF){
                    diff = static_cast<unsigned int>(buffer & 0xFFFFFFFF);
                    b.push_back(diff);
                    memento = buffer;
                    memento >>= 32;
                }
                else{
                    b.push_back(static_cast<unsigned int>(buffer));
                    memento = 0;
                }
            }
            else{
                buffer = static_cast<unsigned int long long>(nombre[i]) + memento;
                if(buffer > 0xFFFFFFFF){
                    b.push_back((static_cast<unsigned int>(buffer & 0xFFFFFFFF)));
                    memento = buffer;
                    memento >>= 32;
                }
                else{
                    b.push_back(static_cast<unsigned int>(buffer));
                    memento = 0;
                }
            }
        }

        i++;
    }
    nombre.swap(b);
}

//Sum
ael::LargeInt& ael::LargeInt::operator+(LargeInt const& a){
    LargeInt& b(*this);
    b += a;
    return b;
}

//Assignment by difference
void ael::LargeInt::operator-=(LargeInt const& a){
    unsigned int quit = 0, i = 0, memento = 0;
    std::vector<unsigned int> b(0);
    unsigned int long long buffer = 0x100000000;

    if(nombre == a.nombre){
        nombre.resize(1);
        nombre[0] = 0;
    }
    else{

    while(quit == 0){
        if(i >= nombre.size()){
            if(i < a.nombre.size()){
                b.push_back((0x100000000 - a.nombre[i]) - memento);
                memento = 1;
                std::cout << "Impossible" << std::endl;
                //system("PAUSE");
            }
            else{
                if(memento != 0){
                    b.push_back(memento);
                }
                quit = 1;
            }
        }
        else{
            if(i < a.nombre.size()){
                if(nombre[i] > (a.nombre[i] + memento)){
                    b.push_back((nombre[i] - a.nombre[i]) - memento);
                    memento = 0;
                }
                else if(nombre[i] == (a.nombre[i] + memento)){
                    b.push_back(0);
                    if(memento != 0){
                        memento = 0;
                    }
                }
                else{
                    buffer += static_cast<unsigned int long long>(nombre[i]);
                    buffer -= static_cast<unsigned int long long>(a.nombre[i]);
                    buffer -= static_cast<unsigned int long long>(memento);
                    b.push_back(static_cast<unsigned int>(buffer));
                    memento = 1;
                    buffer = 0x100000000;
                }
            }
            else{
                if(nombre[i] >= memento){
                    b.push_back(nombre[i] - memento);
                    memento = 0;
                }
                else{
                    //Impossible
                    std::cout << "Impossible 2" << std::endl;
                }
            }
        }
        i++;
    }

    while(b[b.size()-1] == 0){
        b.pop_back();
        if(b.size() == 1){
            break;
        }
    }

    nombre.swap(b);

    }
}

//Difference
ael::LargeInt& ael::LargeInt::operator-(LargeInt const& a){
    LargeInt& b(*this);
    b -= a;
    return b;
}

//Assignment by product
void ael::LargeInt::operator*=(LargeInt const& a){
    std::vector<unsigned int> b(1);
    b[0] = 0;

    unsigned int maxi = 1;
    unsigned int long long buffer = 0, buffer2 = 0, buffer3 = 0;
    for(unsigned int i = 0; i < a.nombre.size(); i++){
        for(unsigned int j = 0; j < nombre.size(); j++){
            if((i+j+1) >= maxi){
                b.push_back(0);
                maxi++;
            }
            buffer = (static_cast<unsigned int long long>(nombre[j]) * static_cast<unsigned int long long>(a.nombre[i])) + static_cast<unsigned int long long>(b[j+i]);

            b[j+i] = static_cast<unsigned int>(buffer & 0xFFFFFFFF);

            buffer >>= 32;

            buffer2 = (static_cast<unsigned int long long>(b[j+i+1]) + buffer + buffer3);

            b[j+i+1] = static_cast<unsigned int>(buffer2 & 0xFFFFFFFF);

            buffer2 >>= 32;

            buffer = 0;

            if(buffer2 > 0){
                buffer3 = buffer2;
            }
            else{
                buffer3 = 0;
            }
        }
        if(buffer3 != 0){
            if(i == (a.nombre.size()-1)){
                b[b.size()-1] += buffer3;
            }
            else{
                b.push_back(static_cast<unsigned int>(buffer3));
            }
        }
        buffer3 = 0;
    }
    while(b[b.size()-1] == 0){
        b.pop_back();
        if(b.size() == 1){
            break;
        }
    }
    nombre.swap(b);
}

//Product
ael::LargeInt& ael::LargeInt::operator*(LargeInt const& a){
    LargeInt& b(*this);
    b *= a;
    return b;
}

//Product very slow
void ael::LargeInt::MultiplicationRusse(LargeInt const& a, LargeInt const& b){
    LargeInt result(0), zero(0), x(0), y(0), aa(a), bb(b);

    if(aa > bb){
        x = b;
        y = a;
    }
    else{
        x = a;
        y = b;
    }

    while(x != zero){
        if((x.nombre[0] & 1) > 0){
            result += y;
        }
        x.ToTheRight();
        y.ToTheLeft();
    }
    nombre.swap(result.nombre);
}

//Assignment by remainder
void ael::LargeInt::operator%=(LargeInt const &a){

    LargeInt gamma(a), n(0), alpha(1), beta(0), reste(0), aa(*this), bb(a), buffer(0), reste2(0), un(1), zero(0);

    if((bb == un) || (aa == bb)){
        nombre.resize(1);
        nombre[0] = 0;
    }
    else if(aa > bb){

    while(gamma <= aa){
        n += un;
        gamma.ToTheLeft();
    }

    //gamma = zero;

    for(LargeInt i(1); i < n; i += un){ //Alpha = 2^(n-1)
        alpha.ToTheLeft();
    }

    beta = alpha;
    beta.ToTheLeft(); //Beta = 2^n = 2^(n-1) * 2 = Alpha * 2

    for(LargeInt j(0); j < n; j += un){
        gamma = alpha;
        gamma += beta;

        gamma.ToTheRight();

        buffer = gamma;
        buffer *= bb;

        if(buffer <= aa){
            alpha = gamma;
        }
        else{
            beta = gamma;
        }
    }

    reste = aa;

    reste2 = alpha;

    reste2 *= bb;

    if(reste2 > reste){
        std::cout << "Error : reste" << std::endl;
        //system("PAUSE");
    }

    if(reste2 == reste){
        reste = zero;
    }
    else if(reste2 < reste){
        reste -= reste2;
    }

    if(reste >= bb){
        std::cout << "Error : reste bigger than require" << std::endl;
        //system("PAUSE");
    }

    nombre.swap(reste.nombre);

    }
}

//Reminder
ael::LargeInt& ael::LargeInt::operator%(LargeInt const& a){
    LargeInt& b(*this);
    b %= a;
    return b;
}

//Modular Exponentiation
void ael::LargeInt::Modular_Exp(LargeInt& exposant, LargeInt& modulo){
    LargeInt result(1), base2(*this), base3(base2), exposant2(exposant), modulo2(modulo), nul(0);

    while(exposant2 != nul){
        if((exposant2.nombre[0] & 0x01) > 0){
            result *= base2;

            result %= modulo2;

        }
        exposant2.ToTheRight();

        base2 *= base2;

        base2 %= modulo2;
    }

    nombre.swap(result.nombre);
}

