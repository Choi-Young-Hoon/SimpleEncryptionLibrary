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
 * 				MD5.cpp
 *
 * Author: informaticien77
 * Release date: 3rd of July 2014
 *
 * ****************************************************************************
 */

#include "AEL.hpp"

unsigned int md5_rotate_left(unsigned int x, unsigned int n) {
  return ((x << n) | (x >> (32-n)));
}

std::vector<unsigned int> ael::MD5(const std::string text){
    //Note: Toutes les variables sont sur 32 bits
    std::vector<unsigned int> message;
    unsigned int lengthMessage[2];

    if(text.size() > 0){
        message.resize(ceil(text.size() / 4.0));

        unsigned int tempo = 0x00;
        for(unsigned int z = 0; z < message.size(); z++){
            message[z] = 0x00;
            for(unsigned int y = 0; (y < 4) && ((y+4*z) < text.size()); y++){
                tempo = text[y+4*z];
                message[z] = (message[z] | (tempo <<= y*8));
            }
        }

        unsigned int long long length = (text.size() * 8) & 0xFFFFFFFFFFFFFFFF;
        lengthMessage[0] = static_cast<unsigned int>(length & 0xFFFFFFFF);
        lengthMessage[1] = static_cast<unsigned int>(length >>= 32);
    }
    else{
        message.resize(1);
        message[0] = 0x00;
        lengthMessage[0] = 0x00;
        lengthMessage[1] = 0x00;
    }

    //Définir r comme suit :
    unsigned int r[64] = {
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
        5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

    unsigned int k[64] = { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee
        ,0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501
        ,0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be
        ,0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821
        ,0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa
        ,0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8
        ,0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed
        ,0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a
        ,0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c
        ,0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70
        ,0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05
        ,0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665
        ,0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039
        ,0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1
        ,0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1
        ,0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };

    //Préparation des variables:
    unsigned int h0 = 0x67452301, h1 = 0xefcdab89, h2 = 0x98badcfe, h3 = 0x10325476;

    //Preparation du message (padding) :
    unsigned int test = 0x80, mes = 0xff;
    while((mes & message[message.size()-1]) != 0){
        test <<= 8;
        mes <<= 8;
    }

    if(test == 0){
         message.push_back(0x80);
    }
    else{
        message[message.size()-1] = (message[message.size()-1] | test);
    }

    while((message.size() % 16) != 14){
        message.push_back(0x00);
    }

    message.push_back(lengthMessage[0]);

    message.push_back(lengthMessage[1]);

    unsigned int a, b, c, d, f, temp, g = 0, w[16];

    //Découpage en blocs de 512 bits:
    for(unsigned int j = 0; j < (message.size() / 16); j++){

        for(unsigned int m = 0; m < 16; m++){
            w[m] = message[m+j*16];
        }

        //initialiser les valeurs de hachage:
        a = h0;
        b = h1;
        c = h2;
        d = h3;

        //Boucle principale:
        for(unsigned int l = 0; l < 64; l++){
            if((l >= 0) && (l <= 15)){
                f = ((b & c) | ((~b) & d)); //Round 1
                g = l;
            }
            else if((l >= 16) && (l <= 31)){
                f = ((d & b) | ((~d) & c)); //Round 2
                g = ((5*l + 1) % 16);
            }
            else if((l >= 32) && (l <= 47)){
                f = ((b ^ c) ^ d); //Round 3
                g = ((3*l + 5) % 16);
            }
            else if((l >= 48) && (l <= 63)){
                f = (c ^ (b | (~d))); //Round 4
                g = ((7*l) % 16);
            }

            temp = d;
            d = c;
            c = b;
            b = (md5_rotate_left((a + f + k[l] + w[g]), r[l]) + b);
            a = temp;

        }

         //ajouter le résultat au bloc précédent:
         h0 = h0 + a;
         h1 = h1 + b;
         h2 = h2 + c;
         h3 = h3 + d;

         //std::cout << std::hex << w[0] << std::endl;

    }

    unsigned int digest[4];
    digest[0] = ((h0>>24)&0xff) | // move byte 3 to byte 0
                    ((h0<<8)&0xff0000) | // move byte 1 to byte 2
                    ((h0>>8)&0xff00) | // move byte 2 to byte 1
                    ((h0<<24)&0xff000000); // byte 0 to byte 3

    digest[1] = ((h1>>24)&0xff) | // move byte 3 to byte 0
                    ((h1<<8)&0xff0000) | // move byte 1 to byte 2
                    ((h1>>8)&0xff00) | // move byte 2 to byte 1
                    ((h1<<24)&0xff000000); // byte 0 to byte 3

    digest[2] = ((h2>>24)&0xff) | // move byte 3 to byte 0
                    ((h2<<8)&0xff0000) | // move byte 1 to byte 2
                    ((h2>>8)&0xff00) | // move byte 2 to byte 1
                    ((h2<<24)&0xff000000); // byte 0 to byte 3

    digest[3] = ((h3>>24)&0xff) | // move byte 3 to byte 0
                    ((h3<<8)&0xff0000) | // move byte 1 to byte 2
                    ((h3>>8)&0xff00) | // move byte 2 to byte 1
                    ((h3<<24)&0xff000000); // byte 0 to byte 3

    /*std::string result = "";

    result += (digest[0] & 0xFF);
    result += ((digest[0] >>= 8) & 0xFF);
    result += ((digest[0] >>= 16) & 0xFF);
    result += ((digest[0] >>= 24) & 0xFF);

    result += (digest[1] & 0xFF);
    result += ((digest[1] >>= 8) & 0xFF);
    result += ((digest[1] >>= 16) & 0xFF);
    result += ((digest[1] >>= 24) & 0xFF);

    result += (digest[2] & 0xFF);
    result += ((digest[2] >>= 8) & 0xFF);
    result += ((digest[2] >>= 16) & 0xFF);
    result += ((digest[2] >>= 24) & 0xFF);

    result += (digest[3] & 0xFF);
    result += ((digest[3] >>= 8) & 0xFF);
    result += ((digest[3] >>= 16) & 0xFF);
    result += ((digest[3] >>= 24) & 0xFF);*/

    std::vector<unsigned int> result;

    result.resize(4);

    result[0] = digest[0];
    result[1] = digest[1];
    result[2] = digest[2];
    result[3] = digest[3];

    return result;
}
