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
//#include "KeyPair.h"
//#include "Key.h"
//#include "BigInt.h"
//#include "RSA.h"
#include "AES.hpp"
//#include "MD5.h"

//Public functions of Advanced Encryption Standard (AES) algorithm.

std::string ael::AES::Encrypt(std::string plaintext, std::string key, int keybits)
{
	int continuer = 1, tourning = 1, sup = 0;
	std::string keyd, results;
	keyd = key.substr(0,16);

	int continuer2 = 1, tour = 0;
	if(keyd[0] != 0 && keyd[1] != 0 && keyd[2] != 0){

		char key1[32] = {0};

		int taillekey = keyd.length(), tailletext = plaintext.length();

		while(continuer2){
			if(tour < taillekey && tour < (keybits / 8)){
				key1[tour] = keyd[tour];
			}
			else{
				continuer2 = 0;
			}
			tour++;
		}

		continuer2 = 1;
		tour = 0;

		char text[16] = {0};

		while(continuer2){
			if(tour < tailletext && tour < 16){
				text[tour] = plaintext[tour];
			}
			else if(tour < 16){
				text[tour] = NULL;
			}
			else{
				continuer2 = 0;
			}
			tour++;
		}

		const unsigned char plaintextt[16] = {text[0],text[1],text[2],text[3],text[4],text[5],text[6],text[7],text[8],text[9],text[10],text[11],text[12],text[13],text[14],text[15]};
		unsigned char finale[16] = {0};

		if(keybits == 128){
			const unsigned char key2[16] = {key1[0],key1[1],key1[2],key1[3],key1[4],key1[5],key1[6],key1[7],key1[8],key1[9],key1[10],key1[11],key1[12],key1[13],key1[14],key1[15]};
			unsigned long rk[44] = {0};
			AESBEncrypt(rk, key2, 128);
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

		str += finale[0];
		str += finale[1];
		str += finale[2];
		str += finale[3];
		str += finale[4];
		str += finale[5];
		str += finale[6];
		str += finale[7];
		str += finale[8];
		str += finale[9];
		str += finale[10];
		str += finale[11];
		str += finale[12];
		str += finale[13];
		str += finale[14];
		str += finale[15];

		return(str);

	}
	else{
		return("empty");
	}
}

std::string ael::AES::Decrypt(std::string text, std::string key, int keybits)
{
	int continuer = 1, tour = 0;
	if(key[0] != 0 && key[1] != 0 && key[2] != 0){

		char key1[32] = {0};

		int sizekey = key.length();

		while(continuer){
			if(tour < sizekey && tour < (keybits / 8)){
				key1[tour] = key[tour];
			}
			/*else if(tour < (keybits / 8)){
				key1[tour] = 32;
			}*/
			else{
				continuer = 0;
			}
			tour++;
		}

		const unsigned char ciphertextt[16] = {text[0],text[1],text[2],text[3],text[4],text[5],text[6],text[7],text[8],text[9],text[10],text[11],text[12],text[13],text[14],text[15]};
		unsigned char finale[16] = {0};

		if(keybits == 128){
			const unsigned char key2[16] = {key1[0],key1[1],key1[2],key1[3],key1[4],key1[5],key1[6],key1[7],key1[8],key1[9],key1[10],key1[11],key1[12],key1[13],key1[14],key1[15]};
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

		if(finale[0] != NULL)
			str += finale[0];
		if(finale[1] != NULL)
			str += finale[1];
		if(finale[2] != NULL)
			str += finale[2];
		if(finale[3] != NULL)
			str += finale[3];
		if(finale[4] != NULL)
			str += finale[4];
		if(finale[5] != NULL)
			str += finale[5];
		if(finale[6] != NULL)
			str += finale[6];
		if(finale[7] != NULL)
			str += finale[7];
		if(finale[8] != NULL)
			str += finale[8];
		if(finale[9] != NULL)
			str += finale[9];
		if(finale[10] != NULL)
			str += finale[10];
		if(finale[11] != NULL)
			str += finale[11];
		if(finale[12] != NULL)
			str += finale[12];
		if(finale[13] != NULL)
			str += finale[13];
		if(finale[14] != NULL)
			str += finale[14];
		if(finale[15] != NULL)
			str += finale[15];

		return(str);

	}
	else{
		return("empty");
	}
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

/*bool ael::RSA::GenerateKeys(unsigned long int digitCount, std::string *moduluskeys, std::string *privatexponent, std::string *publicexponent, unsigned long int precisionOfPrimality)
{
	std::srand(time(NULL));
	KeyPair kp = RSAH::GenerateKeyPair(digitCount, precisionOfPrimality);
	Key privatekey = kp.GetPrivateKey(), publickey = kp.GetPublicKey();
	BigInt privkmod = privatekey.GetModulus(), privkexp = privatekey.GetExponent(), publikmod = publickey.GetModulus(), publikexp = publickey.GetExponent();
	std::string privkmodt = privkmod.ToString(), privkexpt = privkexp, publikmodt = publikmod, publikexpt = publikexp;

	if(privkmodt == publikmodt){
		*moduluskeys = publikmodt;
		*privatexponent = privkexpt;
		*publicexponent = publikexpt;
		return true;
	}
	else{
		return false;
	}
}

std::string ec::RSA::Encrypt(std::string plaintext, std::string keymod, std::string keyexp)
{
	BigInt keymods = keymod, keyexps = keyexp;
	std::string encrypted = RSAH::Encrypt(plaintext, Key(keymods, keyexps));
	return encrypted;
}

std::string ec::RSA::Decrypt(std::string cyphertext, std::string keymod, std::string keyexp)
{
	BigInt keymods = keymod, keyexps = keyexp;
	std::string decrypted = RSAH::Decrypt(cyphertext, Key(keymods, keyexps));
	return decrypted;
}*/

/*std::string ael::HASH::MD5(const std::string text){
    std::string hashs = md5(text);
    return hashs;
}*/
