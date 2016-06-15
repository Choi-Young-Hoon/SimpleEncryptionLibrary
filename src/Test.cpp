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
 * 				Test.cpp
 *
 * Author: informaticien77
 * Release date: 28th of June 2014
 *
 * ****************************************************************************
 */


#include "SEL.hpp"

bool TestDiffieHellman(void){
    sel::LargeInt p(0), g(0), A(0), B(0), a(0), b(0), s1(0), s2(0), one(1), two(2), six(6), p1(0), p2(0);

    //ael::randinit();
    //p.BitGenerator(1024);
    p.Generate(4); //128 Bits
    p = p*six;
    p1 = p - one;
    p2 = p + one;

    //while((!p1.MillerRabinPrimality(6)) && (!p2.MillerRabinPrimality(6))){
    while((!p1.FermatPrimality()) && (!p2.FermatPrimality())){
        //p.BitGenerator(1024);
        p1 += six;
        //p1.Generate(8);
        p2 += six;
        //p2.Generate(8);
        std::cout << "ONE TURN" << std::endl;
    }

    g.BitGenerator(64);

    a.BitGenerator(384);

	std::cout << "FOUND !" << std::endl;
    //std::getchar();

    b.BitGenerator(384);
    A = g;
    A.Modular_Exp(a, p);
    B = g;
    B.Modular_Exp(b, p);
    s1 = B;
    s1.Modular_Exp(a, p);
    s2 = A;
    s2.Modular_Exp(b, p);

    if(s1 == s2){
        return true;
    }
    else{
        return false;
    }
}

int main(){
		std::cout << "Test program of SEL launched ..." << std::endl << std::endl;

		//License information
		std::cout << "This program and all source files of the Simple Encryption Library are under the Lesser General Public License (LGPL). See COPYING and LESSER.COPYING files which you should have with the source code." << std::endl << std::endl;

        //Random generators initialization
        sel::randinit();

		//Test the AES-128Bits algorithm
		std::cout << "AES 128 Bits : ";
		sel::AES key_aes_128;
		key_aes_128.GenerateKey(128);
		std::string encrypt128 = key_aes_128.Encrypt("Test program ...");
		std::string decrypt128 = key_aes_128.Decrypt(encrypt128);

		if(decrypt128 == "Test program ..."){
			std::cout << "OK" << std::endl;
		}
		else{
			std::cout << "FAILED" << std::endl;
		}

		//Test the AES-192Bits algorithm
		std::cout << "AES 192 Bits : ";
		sel::AES key_aes_192;
		key_aes_192.GenerateKey(192);
		std::string encrypt192 = key_aes_192.Encrypt("Test program ...");
		std::string decrypt192 = key_aes_192.Decrypt(encrypt192);

		if(decrypt192 == "Test program ..."){
			std::cout << "OK" << std::endl;
		}
		else{
			std::cout << "FAILED" << std::endl;
		}

		//Test the AES-256Bits algorithm
		std::cout << "AES 256 Bits : ";
		sel::AES key_aes_256;
		key_aes_256.GenerateKey(256);
		std::string encrypt256 = key_aes_256.Encrypt("Test program ...");
		std::string decrypt256 = key_aes_256.Decrypt(encrypt256);

		if(decrypt256 == "Test program ..."){
			std::cout << "OK" << std::endl;
		}
		else{
			std::cout << "FAILED" << std::endl;
		}

		//Test the MD5 algorithm
		std::cout << "MD5 : ";
		sel::MD5 md5("Hello world !");
		if(md5.asHexString() == "67c18d060479c5d867c9b91c80edeb4c"){
			std::cout << "OK" << std::endl;
		}
		else{
			std::cout << "FAILED" << std::endl;
		}

        //Test the Diffie-Hellman Key Exchange algorithm
		std::cout << "Diffie-Hellman Key Exchange : ";

		if(TestDiffieHellman()){
			std::cout << "OK" << std::endl;
		}
		else{
			std::cout << "FAILED" << std::endl;
		}

		std::cout << "Press a touch to quit ..." << std::endl;
		std::getchar();

        return 0;

}
