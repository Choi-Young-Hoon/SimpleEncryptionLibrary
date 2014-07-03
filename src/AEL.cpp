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

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include "AEL.hpp"
#include "AES.hpp"

//Public functions of Advanced Encryption Standard (AES) algorithm.

std::string ael::AES::Encrypt(std::string plaintext, std::string key, int keybits)
{
	int tailletext = plaintext.length();

    unsigned char text[16] = {0};

    for(unsigned int i = 0; i < 16; i++){
        if(i < tailletext){
            text[i] = plaintext[i];
        }
        else{
            text[i] = 0;
        }
    }

    const unsigned char plaintextt[16] = {text[0],text[1],text[2],text[3],text[4],text[5],text[6],text[7],text[8],text[9],text[10],text[11],text[12],text[13],text[14],text[15]};
    unsigned char finale[16] = {0};

    if(keybits == 128){
        const unsigned char keyy[16] = {key[0],key[1],key[2],key[3],key[4],key[5],key[6],key[7],key[8],key[9],key[10],key[11],key[12],key[13],key[14],key[15]};
        unsigned long rk[44] = {0};
        AESBEncrypt(rk, keyy, 128);
        AESEncrypt(rk, 10, plaintextt, finale);
    }
    else if(keybits == 192){
        const unsigned char keyy[24] = {key[0],key[1],key[2],key[3],key[4],key[5],key[6],key[7],key[8],key[9],key[10],key[11],key[12],key[13],key[14],key[15],key[16],key[17],key[18],key[19],key[20],key[21],key[22],key[23]};
        unsigned long rk[52] = {0};
        AESBEncrypt(rk, keyy, 192);
        AESEncrypt(rk, 12, plaintextt, finale);
    }
    else if(keybits == 256){
        const unsigned char keyy[32] = {key[0],key[1],key[2],key[3],key[4],key[5],key[6],key[7],key[8],key[9],key[10],key[11],key[12],key[13],key[14],key[15],key[16],key[17],key[18],key[19],key[20],key[21],key[22],key[23],key[24],key[25],key[26],key[27],key[28],key[29],key[30],key[31]};
        unsigned long rk[60] = {0};
        AESBEncrypt(rk, keyy, 256);
        AESEncrypt(rk, 14, plaintextt, finale);
    }
    else{
        return("invalid size");
    }

    std::string str;

    str.clear();

    for(unsigned int j = 0; j < 16; j++){
        str += finale[j];
    }

    return(str);
}

std::string ael::AES::Decrypt(std::string text, std::string key, int keybits)
{
    const unsigned char ciphertextt[16] = {text[0],text[1],text[2],text[3],text[4],text[5],text[6],text[7],text[8],text[9],text[10],text[11],text[12],text[13],text[14],text[15]};
    unsigned char finale[16] = {0};

    if(keybits == 128){
        const unsigned char key2[16] = {key[0],key[1],key[2],key[3],key[4],key[5],key[6],key[7],key[8],key[9],key[10],key[11],key[12],key[13],key[14],key[15]};
        unsigned long rk[44] = {0};
        AESBDecrypt(rk, key2, 128);
        AESDecrypt(rk, 10, ciphertextt, finale);
    }
    else if(keybits == 192){
        const unsigned char key2[24] = {key[0],key[1],key[2],key[3],key[4],key[5],key[6],key[7],key[8],key[9],key[10],key[11],key[12],key[13],key[14],key[15],key[16],key[17],key[18],key[19],key[20],key[21],key[22],key[23]};
        unsigned long rk[52] = {0};
        AESBDecrypt(rk, key2, 192);
        AESDecrypt(rk, 12, ciphertextt, finale);
    }
    else if(keybits == 256){
        const unsigned char key2[32] = {key[0],key[1],key[2],key[3],key[4],key[5],key[6],key[7],key[8],key[9],key[10],key[11],key[12],key[13],key[14],key[15],key[16],key[17],key[18],key[19],key[20],key[21],key[22],key[23],key[24],key[25],key[26],key[27],key[28],key[29],key[30],key[31]};
        unsigned long rk[60] = {0};
        AESBDecrypt(rk, key2, 256);
        AESDecrypt(rk, 14, ciphertextt, finale);
    }
    else{
        return("invalid size");
    }

    std::string str;

    str.clear();

    for(unsigned int j = 0; j < 16; j++){
        str += finale[j];
    }

    return(str);
}

std::string ael::AES::GenerateKey(int keybits)
{
	std::srand(time(NULL));
	std::string key;
	int i = 0;
	for(i = 0; i < (keybits/8); i++){
		key += std::rand()%255;
	}
	return key;
}

std::string ael::Vector_UInt_To_String(std::vector<unsigned int> text){
    std::string result = "";
    for(unsigned int i = 0; i < text.size(); i++){
        result += (text[i] & 0xFF);
        result += ((text[i] >>= 8) & 0xFF);
        result += ((text[i] >>= 16) & 0xFF);
        result += ((text[i] >>= 24) & 0xFF);
    }
    return result;
}

std::string ael::Vector_UInt_To_Hex_String(std::vector<unsigned int> text){
    std::ostringstream ss;
    for(unsigned int i = 0; i < text.size(); i++){
        ss << std::setfill('0') << std::setw(8) << std::hex << text[i];
    }
    return ss.str();
}
