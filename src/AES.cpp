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
 * 				AES.cpp
 *
 * Author: informaticien77
 * Release date: 4th of July 2014
 *
 * ****************************************************************************
 */

#include "AEL.hpp"
#include "AES.hpp"

//Public functions of Advanced Encryption Standard (AES) algorithm.

ael::AES::AES(){
    aes_key = "";
}

ael::AES::AES(std::string key){
    if(key.size() == 16){
        aes_key = key;
    }
    else if(key.size() == 24){
        aes_key = key;
    }
    else if(key.size() == 32){
        aes_key = key;
    }
    else{
        aes_key = "Key length error !";
    }
}

void ael::AES::GenerateKey(int keybits){
    std::srand(time(NULL));
	aes_key = "";
	int i = 0;
	for(i = 0; i < (keybits/8); i++){
		aes_key += std::rand()%256;
	}
}

std::string ael::AES::Encrypt(std::string plaintext)
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

    if((aes_key.size()*8) == 128){
        unsigned long rk[44] = {0};
        AESBEncrypt(rk, (const unsigned char *)aes_key.c_str(), 128);
        AESEncrypt(rk, 10, plaintextt, finale);
    }
    else if((aes_key.size()*8) == 192){
        unsigned long rk[52] = {0};
        AESBEncrypt(rk, (const unsigned char *)aes_key.c_str(), 192);
        AESEncrypt(rk, 12, plaintextt, finale);
    }
    else if((aes_key.size()*8) == 256){
        unsigned long rk[60] = {0};
        AESBEncrypt(rk, (const unsigned char *)aes_key.c_str(), 256);
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

std::string ael::AES::Decrypt(std::string text)
{
    const unsigned char ciphertextt[16] = {text[0],text[1],text[2],text[3],text[4],text[5],text[6],text[7],text[8],text[9],text[10],text[11],text[12],text[13],text[14],text[15]};
    unsigned char finale[16] = {0};

    if((aes_key.size()*8) == 128){
        unsigned long rk[44] = {0};
        AESBDecrypt(rk, (const unsigned char *)aes_key.c_str(), 128);
        AESDecrypt(rk, 10, ciphertextt, finale);
    }
    else if((aes_key.size()*8) == 192){
        unsigned long rk[52] = {0};
        AESBDecrypt(rk, (const unsigned char *)aes_key.c_str(), 192);
        AESDecrypt(rk, 12, ciphertextt, finale);
    }
    else if((aes_key.size()*8) == 256){
        unsigned long rk[60] = {0};
        AESBDecrypt(rk, (const unsigned char *)aes_key.c_str(), 256);
        AESDecrypt(rk, 14, ciphertextt, finale);
    }
    else{
        return("Invalid key size !");
    }

    std::string str;

    str.clear();

    for(unsigned int j = 0; j < 16; j++){
        str += finale[j];
    }

    return(str);
}
