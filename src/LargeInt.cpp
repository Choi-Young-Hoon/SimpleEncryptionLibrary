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

//Constructor
sel::LargeInt::LargeInt(){
    number.clear();
}

//Vector of uint32 to LargeInt
sel::LargeInt::LargeInt(std::vector<uint32_t> &a){
    number = a;
}

//String in hexadecimal to LargeInt
sel::LargeInt::LargeInt(std::string a){
    std::reverse(a.begin(), a.end());

    number.clear();

    std::string current_number;

    for(int i = 0; i < a.size(); i += 8){
        current_number = a.substr(i, 8);
        std::reverse(current_number.begin(), current_number.end());
        number.push_back(std::strtoul(current_number.c_str(), 0, 16));
    }
}

//Init the random function
void sel::randinit(void){
    std::srand(time(NULL));
}

//Get the bit in the position wanted
bool sel::LargeInt::getbit(const uint32_t position){
    uint32_t posblock = position << 5, posbit = position % 32;
    uint32_t block = number[posblock], posfinal = 0x01;
    posfinal <<= posbit;
    return((posfinal & block) > 0);
}

//Set a bit value
void sel::LargeInt::setbit(const bool bit, const uint32_t position){
    uint32_t posblock = position >> 5, posbit = position % 32;
    uint32_t block = number[posblock];

    uint32_t posfinal = 0x01;
    posfinal = posfinal << posbit;

    if(bit){
        number[posblock] = block | posfinal;
    }
    else{
        posfinal = ~posfinal;
        number[posblock] = block & posfinal;
    }

    if(number[posblock] == 0){
        number.pop_back();
    }
}

//Number of bits
uint32_t sel::LargeInt::size_bits() const {

    uint32_t l = number.size();

    uint32_t last = number[l-1];

    if (last == 0){
        return 0;
    }

    l <<= 5;

    for(uint32_t i=0x80000000; i>0; i>>=1){
        if((last & i) > 0){
            break;
        }
        else if (l > 0){
            l -= 1;
        }
        else{
            break;
        }
    }
    return l;
}

//Number of element in vector
uint32_t sel::LargeInt::size() const {
    return number.size();
}

//Char to LargeInt
sel::LargeInt::LargeInt(unsigned char a[], uint16_t size){
    uint16_t taille = ceil(size / 4.0), h = 0;
    number.resize(taille);
    for(uint16_t i = 0; i < taille; i++){
        number[i] = 0;
		for(uint16_t j = 0; j < 4; j++){
			h = i<<2 + j;
			if(h < size){
				h = a[h];
				h <<= (j<<3);
				number[i] += h;
			}
		}
    }
}

//Copy from another LargeInt
sel::LargeInt::LargeInt(LargeInt const& a){
    number = a.number;
}

//Put a value to the first array of the LargeInt
sel::LargeInt::LargeInt(unsigned int a){
    number.resize(1);
    number[0] = a;
}

//Destructor
sel::LargeInt::~LargeInt(){

}

//Convert LargeInt to a 64 type string
std::string sel::LargeInt::as64String(void){
    unsigned int asize = (number.size() << 2);
    unsigned char a[asize];

    for(unsigned int i = 0; i < number.size(); i++){
        a[(i << 2)] = (number[i] & 0xFF);
        a[(i << 2) + 1] = ((number[i] >> 8) & 0xFF);
        a[(i << 2) + 2] = ((number[i] >> 16) & 0xFF);
        a[(i << 2) + 3] = ((number[i] >> 24) & 0xFF);
    }

    unsigned int bsize = ceil(4.0/3.0 * asize);
    unsigned char b[bsize];

    for(unsigned int j = 0; j < floor(bsize / 3.0); j++){
        b[(j << 2)] = ((a[j * 3] & 0xFC) >> 2);
        b[(j << 2) + 1] = ((a[j * 3] & 0x03) << 4) | ((a[j * 3 + 1] & 0xF0) >> 4);
        b[(j << 2) + 2] = ((a[j * 3 + 1] & 0x0F) << 2) | ((a[j * 3 + 2] & 0xC0) >> 6);
        b[(j << 2) + 3] = (a[j * 3 + 2] & 0x3F);
    }

    unsigned int complement = 0;

    if(floor(4.0 / 3.0 * asize) != ceil(4.0 / 3.0 * asize)){
        unsigned int dsize = (asize % 3);

        if(dsize == 1){
            b[bsize - 2] = ((a[asize - 1] & 0xFC) >> 2);
            b[bsize - 1] = ((a[asize - 1] & 0x03) << 4);
            complement = 2;
        }
        else if(dsize == 2){
            b[bsize - 3] = ((a[asize - 2] & 0xFC) >> 2);
            b[bsize - 2] = ((a[asize - 2] & 0x03) << 4) | ((a[asize - 1] & 0xF0) >> 4);
            b[bsize - 1] = ((a[asize - 1] & 0x0F) << 2);
            complement = 1;
        }
    }

    unsigned char c[65] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/', '='};

    std::string d;

    for(unsigned int k = 0; k < bsize; k++){
        d += c[(b[k])];
    }

    if(complement == 1){
        d += c[64];
    }
    else if(complement == 2){
        d += c[64];
        d += c[64];
    }

    return d;
}

std::vector<uint32_t> sel::LargeInt::asVector(void){
    std::vector<uint32_t> a_copy;
    a_copy = number;
    return a_copy;
}

//Show the LargeInt value in the console
void sel::LargeInt::Show() const{
    for(int16_t i = number.size() - 1; i >= 0; i--){
        std::cout << std::hex << number[i] << " ";
    }
    std::cout << std::endl;
}

//Move to the right all the bits of the LargeInt
void sel::LargeInt::ToTheRight(){
    uint8_t buffer = 0, buffer_before = 0;
    uint16_t numbersize = number.size();

    for(int16_t i = (numbersize - 1); i >= 0; i--){
        buffer = number[i] & 1;
        number[i] >>= 1;
        number[i] |= (buffer_before * 0x80000000);
        buffer_before = buffer;
    }

    if(number[numbersize - 1] == 0 && numbersize > 1){
        number.pop_back();
    }
}

//Move to the left all the bits of the LargeInt
void sel::LargeInt::ToTheLeft(){
    uint8_t buffer = 0, buffer_before = 0;
    uint16_t numbersize = number.size();

    for(uint16_t i = 0; i < numbersize; i++){
        buffer = (number[i] & 0x80000000) > 0;
        number[i] <<= 1;
        number[i] |= buffer_before;
        buffer_before = buffer;
    }

    if(buffer != 0){
        number.push_back(buffer);
    }
}

//Generate a pseudo-random number
//This function have to be more close of a random number in the future
void sel::LargeInt::Generate(unsigned int taille){
    number.resize(taille);

    for(unsigned int i = 0; i < number.size(); i++){
        number[i] = (std::rand()*std::rand()) % 0x100000000;
    }

    number[0] &= 0xFFFFFFFB;

    if((number[0] & 0x01) == 0){
        number[0] |= 0x01;
    }

}

//Generate a pseudo-random number include between two limits
//Also this function will be improve
void sel::LargeInt::NumberGenerator(LargeInt& maxi, LargeInt& mini){
    uint32_t integerlenght = 0, extrasize = 1, filter = 0, random = 0;
    bool start = true;

    if(maxi.number.size() == mini.number.size()){
        integerlenght = maxi.size();
    }
    else{
        integerlenght = ((std::rand()) % (maxi.size() - mini.size())) + mini.size();
    }
    number.resize(integerlenght);

    while(extrasize != 0 && extrasize < maxi.number[maxi.size()-1]){
        extrasize <<= 1;
    }

    if((extrasize == 0) || (maxi.number[maxi.size()-1] == 1)){
        filter = 0xFFFFFFFF;
    }
    else{
        filter = (extrasize - 1);
    }

    random = (rand()*rand()) % 0x100000000;

    while((*this < mini) || (*this > maxi) || (start)){

        for(uint32_t k = 0; k < integerlenght; k++){
            random = (rand()*random) % 0x100000000;
            number[k] = (random + rand()) % 0x100000000;
        }

        number[number.size() - 1] = (number[number.size() - 1] & filter);

        while((number[number.size() - 1] < mini.number[mini.size()-1]) && (number.size() == mini.size())){
            number[number.size() - 1] <<= 1;
            number[number.size() - 1] += (rand() % 0x100);
        }

        if((maxi.size() == mini.size()) && (maxi.size() == integerlenght)){
            number[number.size() - 1] = (((number[number.size() - 1] * number[number.size() - 1]) % (maxi.number[maxi.size()-1] - mini.number[mini.number.size()-1])) + mini.number[mini.number.size()-1]);
        }

        if((number[number.size()-1] == 0) && (number.size() > 1)){
            number.pop_back();
        }

        if(start){
            start = false;
        }
    }
    number[0] = (number[0] | 0x1);
}

//Get the first array of the vector number.
uint32_t sel::LargeInt::GetFirst(){
    return number[0];
}

//Is equal operator
bool sel::LargeInt::operator==(LargeInt const& a){
    return (number == a.number);
}

//Isn't equal operator
bool sel::LargeInt::operator!=(LargeInt const& a){
    return (number != a.number);
}

//Inferior operator
bool sel::LargeInt::operator<(LargeInt const& a){
    bool state = false;
    uint16_t numbersize = number.size(), asize = a.number.size();

    if(numbersize < asize){
        return true;
    }
    else if(numbersize > asize){
        return false;
    }
    else if(number == a.number){
        return false;
    }
    else{
        for(int16_t i = (numbersize - 1); i >= 0; i--){
            if(number[i] < a.number[i]){
                state = true;
                break;
            }
            else if(number[i] > a.number[i]){
                state = false;
                break;
            }
        }
        return state;
    }
}

//Inferior or equal operator
bool sel::LargeInt::operator<=(LargeInt const& a){
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
bool sel::LargeInt::operator>(LargeInt const& a){
    if(*this <= a){
        return false;
    }
    else{
        return true;
    }
}

//Superior or equal operator
bool sel::LargeInt::operator>=(LargeInt const& a){
    if(*this < a){
        return false;
    }
    else{
        return true;
    }
}

//Equal operator
sel::LargeInt& sel::LargeInt::operator=(LargeInt const& a){
    number = a.number;

    return *this;
}

//Assignment by sum
void sel::LargeInt::operator+=(LargeInt const& a){
    uint32_t buffer = 0, memento = 0;
    uint8_t i = 0;
    bool quit = false;
    std::vector<uint32_t> b(0);

    while(!quit){
        if(i >= number.size()){
            if(i < a.size()){
                buffer = a.number[i] + memento;

                if(buffer < a.number[i]){ //Overflow
                    memento = 1;
                }
                else{
                    memento = 0;
                }

                b.push_back(buffer);

            }
            else{
                if(memento != 0){
                    b.push_back(memento);
                }

                quit = true;
            }
        }
        else{
            if(i < a.size()){
                buffer = number[i] + a.number[i] + memento;

                if((buffer < number[i]) || (buffer < a.number[i])){ //Overflow
                    memento = 1;
                }
                else{
                    memento = 0;
                }

                b.push_back(buffer);
            }
            else{
                buffer = number[i] + memento;

                if((buffer < number[i]) || (buffer < memento)){ //Overflow
                    memento = 1;
                }
                else{
                    memento = 0;
                }

                b.push_back(buffer);
            }
        }

        i++;
    }
    number.swap(b);
}

//Sum
sel::LargeInt sel::LargeInt::operator+(LargeInt const& a){
    LargeInt b(*this);
    b += a;
    return b;
}

//Assignment by difference
//Result must be positive
void sel::LargeInt::operator-=(LargeInt const& a){
    uint32_t memento = 0, temp_sum = 0;
    uint8_t i = 0;
    bool quit = false;
    std::vector<uint32_t> b(0);

    if(number == a.number || *this < a){
        number.resize(1);
        number[0] = 0;
    }
    else{

    while(!quit){
        if(i >= number.size()){
            if(memento != 0){
                b.push_back(memento);
            }
            quit = true;
        }
        else{
            if(i < a.number.size()){
                b.push_back((number[i] - a.number[i]) - memento);
                temp_sum = a.number[i] + memento;

                if((temp_sum < a.number[i]) || (temp_sum < memento)){ //Overflow
                    memento = 1;
                }
                else{
                    if(number[i] >= temp_sum){
                        memento = 0;
                    }
                    else{
                        memento = 1;
                    }
                }
            }
            else{
                b.push_back(number[i] - memento);
                memento = 0;
            }
        }
        i++;
    }

    while(b.size() > 1 && b[b.size()-1] == 0){
        b.pop_back();
    }

    number.swap(b);

    }
}

//Difference
sel::LargeInt sel::LargeInt::operator-(LargeInt const& a){
    LargeInt b(*this);
    b -= a;
    return b;
}

//Assignment by product
void sel::LargeInt::operator*=(LargeInt const& a){
    std::vector<uint32_t> b(1);
    b[0] = 0;

    uint32_t maxi = 1;
    uint64_t buffer = 0, buffer2 = 0, buffer3 = 0;
    for(uint32_t i = 0; i < a.number.size(); i++){
        for(uint32_t j = 0; j < number.size(); j++){
            if((i+j+1) >= maxi){
                b.push_back(0);
                maxi++;
            }

            buffer = (static_cast<uint64_t>(number[j]) * static_cast<uint64_t>(a.number[i])) + static_cast<uint64_t>(b[j+i]);

            b[j+i] = static_cast<uint32_t>(buffer & 0xFFFFFFFF);

            buffer >>= 32;

            buffer2 = (static_cast<uint64_t>(b[j+i+1]) + buffer + buffer3);

            b[j+i+1] = static_cast<uint32_t>(buffer2 & 0xFFFFFFFF);

            buffer2 >>= 32;

            buffer = 0;

            buffer3 = buffer2;
        }

        if(buffer3 != 0){
            if(i == (a.size() - 1)){
                b[b.size() - 1] += buffer3;
            }
            else{
                b.push_back(static_cast<uint32_t>(buffer3));
            }
        }

        buffer3 = 0;
    }
    while(b.size() > 1 && b[b.size()-1] == 0){
        b.pop_back();
    }
    number.swap(b);
}

//Product
sel::LargeInt sel::LargeInt::operator*(LargeInt const& a){
    LargeInt b(*this);
    b *= a;
    return b;
}

//Multiplication very slow
sel::LargeInt sel::LargeInt::mul_russian(LargeInt const& b){
    LargeInt result(0), zero(0), x(0), y(0), aa(*this), bb(b);

    if(aa > bb){
        x = b;
        y = *this;
    }
    else{
        x = *this;
        y = b;
    }

    while(x != zero){
        if((x.number[0] & 1) > 0){
            result += y;
        }
        x.ToTheRight();
        y.ToTheLeft();
    }
    return result;
}

sel::LargeInt sel::LargeInt::mul_karatsuba(LargeInt const& y){
    //Cut the numbers near the middle
    uint16_t size_of_x = (*this).size(), size_of_y = y.size(), cut_index = std::max(size_of_x, size_of_y) >> 1;
    sel::LargeInt result(0);

    if(cut_index >= size_of_x){
        std::vector<uint32_t> y_high, y_low;

        for(uint16_t i = 0; i < cut_index; i++){
            y_low.push_back(y.number[i]);
        }

        for(uint16_t i = cut_index; i < size_of_y; i++){
            y_high.push_back(y.number[i]);
        }

        sel::LargeInt y0(y_low), y1(y_high);

        result =((*this) * y0) + (((*this) * y1) << (cut_index << 5));
    }
    else if(cut_index >= size_of_y){
        std::vector<uint32_t> x_high, x_low;

        for(uint16_t i = 0; i < cut_index; i++){
            x_low.push_back(number[i]);
        }

        for(uint16_t i = cut_index; i < size_of_x; i++){
            x_high.push_back(number[i]);
        }

        sel::LargeInt x0(x_low), x1(x_high);

        result =(x0 * y) + ((x1 * y) << (cut_index << 5));
    }
    else{
        std::vector<uint32_t> x_high, x_low, y_high, y_low;
        bool add = false;

        for(uint16_t i = 0; i < cut_index; i++){
            x_low.push_back(number[i]);
        }

        for(uint16_t i = cut_index; i < size_of_x; i++){
            x_high.push_back(number[i]);
        }

        for(uint16_t i = 0; i < cut_index; i++){
            y_low.push_back(y.number[i]);
        }

        for(uint16_t i = cut_index; i < size_of_y; i++){
            y_high.push_back(y.number[i]);
        }

        sel::LargeInt x0(x_low), x1(x_high), y0(y_low), y1(y_high), sum(0), one(1), power_separator(1);
        power_separator <<= ((cut_index) << 5);

        if(x1 < x0){
            add = ~add;
            sum = x0 - x1;
        }
        else{
            sum = x1 - x0;
        }

        if(y1 < y0){
            add = ~add;
            sum *= (y0 - y1);
        }
        else{
            sum *= (y1 - y0);
        }

        result = ((power_separator * power_separator + power_separator) * x1 * y1) + ((power_separator + one) * x0 * y0);

        if(add){
            result += power_separator * sum;
        }
        else{
            result -= power_separator * sum;
        }
    }

    return result;
}

//Assignment by remainder
void sel::LargeInt::operator%=(LargeInt const &a){

    LargeInt gamma(a), alpha(1), beta(0), remainder(0), dividend(*this), divisor(a), remainder2(0), un(1), zero(0);
    uint32_t n = 0;

    if((divisor == un) || (dividend == divisor)){
        number.clear();
        number.insert(number.begin(), 0);
    }
    else if(dividend > divisor)
    {

        n = dividend.size_bits() - gamma.size_bits();

        gamma <<= n;

        while(gamma <= dividend){
            n++;
            gamma.ToTheLeft();
        }

        alpha <<= n - 1; //Alpha = 2^(n-1)

        beta = alpha;
        beta.ToTheLeft(); //Beta = 2^n = 2^(n-1) * 2 = Alpha * 2

        for(uint32_t j = 0; j < n; j++){
            gamma = alpha + beta;

            gamma.ToTheRight();

            if(gamma * divisor <= dividend){
                alpha = gamma;
            }
            else{
                beta = gamma;
            }
        }

        remainder = dividend;

        remainder2 = alpha * divisor;

        if(remainder2 > remainder){
            //Error
            std::cout << "Error remainder 1" << std::endl;
        }

        if(remainder2 == remainder){
            remainder = zero;
        }
        else if(remainder2 < remainder){
            remainder -= remainder2;
        }

        if(remainder >= divisor){
            //Error
            std::cout << "Error remainder 2" << std::endl;
        }

        number.swap(remainder.number);
    }
}

//Remainder
sel::LargeInt sel::LargeInt::operator%(LargeInt const& a){
    LargeInt b(*this);
    b %= a;
    return b;
}

//Modular Exponentiation
void sel::LargeInt::Modular_Exp(LargeInt& exposant, LargeInt& modulo){
    LargeInt result(1), base2(*this), modulo2(modulo), nul(0);

    for(sel::LargeInt exposant2(exposant); exposant2 > nul; exposant2.ToTheRight()){
        if((exposant2.number[0] & 0x1) > 0){
            result *= base2;

            result %= modulo2;

        }

        base2 *= base2;

        base2 %= modulo2;
    }

    number.swap(result.number);
}

void sel::LargeInt::operator<<=(const uint32_t shifts){
    uint32_t shifts_32 = shifts >> 5, shifts_left = shifts % 32;

    for(shifts_32; shifts_32 > 0; shifts_32--){
        number.insert(number.begin(), 0);
    }

    for(shifts_left; shifts_left > 0; shifts_left--){
        (*this).ToTheLeft();
    }
}

void sel::LargeInt::operator>>=(const uint32_t shifts){
    uint32_t shifts_32 = shifts >> 5, shifts_left = shifts % 32;

    for(shifts_32; shifts_32 > 0; shifts_32--){
        number.erase(number.begin());
    }

    for(shifts_left; shifts_left > 0; shifts_left--){
        (*this).ToTheRight();
    }
}

sel::LargeInt sel::LargeInt::operator<<(const uint32_t shifts){
    sel::LargeInt result(*this);

    result <<= shifts;

    return result;
}

sel::LargeInt sel::LargeInt::operator>>(const uint32_t shifts){
    sel::LargeInt result(*this);

    result >>= shifts;

    return result;
}

void sel::LargeInt::operator&=(LargeInt const& y){
    for(uint16_t i = 0; i < std::min(number.size(), y.number.size()); i++){
        number[i] &= y.number[i];
    }

    while(number.size() > y.size()){
        number.pop_back();
    }
}

sel::LargeInt sel::LargeInt::operator&(LargeInt const& y){
    sel::LargeInt result(*this);

    result &= y;

    return result;
}

void sel::LargeInt::operator|=(LargeInt const& y){
    for(uint16_t i = 0; i < std::min(number.size(), y.number.size()); i++){
        number[i] |= y.number[i];
    }

    for(uint16_t i = number.size(); i < y.size(); i++){
        number.push_back(y.number[i]);
    }
}

sel::LargeInt sel::LargeInt::operator|(LargeInt const& y){
    sel::LargeInt result(*this);

    result |= y;

    return result;
}

void sel::LargeInt::operator^=(LargeInt const& y){
    for(uint16_t i = 0; i < std::min(number.size(), y.number.size()); i++){
        number[i] ^= y.number[i];
    }

    for(uint16_t i = number.size(); i < y.size(); i++){
        number.push_back(y.number[i]);
    }
}

sel::LargeInt sel::LargeInt::operator^(LargeInt const& y){
    sel::LargeInt result(*this);

    result ^= y;

    return result;
}

sel::LargeInt sel::LargeInt::operator~(void){
    sel::LargeInt result(*this);

    for(uint16_t i = 0; i < number.size(); i++){
        result.number[i] = ~result.number[i];
    }

    return result;
}
