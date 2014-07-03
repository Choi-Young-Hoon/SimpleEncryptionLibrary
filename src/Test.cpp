#include <iostream>
#include "AEL.hpp"

bool TestDiffieHellman(void){
    ael::LargeInt p(0), g(0), A(0), B(0), a(0), b(0), s1(0), s2(0);

    p = ael::Algo::BitGenerator(128);

    while(!ael::Algo::FermatPrimality(p)){
    //while(!MillerRabinPrimality(p, 6)){
        p = ael::Algo::BitGenerator(128);
    }

    g = ael::Algo::BitGenerator(64);

    a = ael::Algo::BitGenerator(384);

	//std::cout << "Press a touch ..." << std::endl;
    //std::getchar();

    b = ael::Algo::BitGenerator(384);
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

		std::cout << "Test program of AEL launched ..." << std::endl << std::endl;

		//License information
		std::cout << "This program and all source files of the Advanced Encryption Library are under the Lesser General Public License (LGPL). See COPYING and LESSER.COPYING files which you should have with the source code." << std::endl << std::endl;

		//Test the AES-128Bits algorithm
		std::cout << "AES 128 Bits : ";
		std::string key128 = ael::AES::GenerateKey(128);
		std::string encrypt128 = ael::AES::Encrypt("Test program ...", key128, 128);
		std::string decrypt128 = ael::AES::Decrypt(encrypt128, key128, 128);

		if(decrypt128 == "Test program ..."){
			std::cout << "OK" << std::endl;
		}
		else{
			std::cout << "FAILED" << std::endl;
		}

		//Test the AES-192Bits algorithm
		std::cout << "AES 192 Bits : ";
		std::string key192 = ael::AES::GenerateKey(192);
		std::string encrypt192 = ael::AES::Encrypt("Test program ...", key192, 192);
		std::string decrypt192 = ael::AES::Decrypt(encrypt192, key192, 192);

		if(decrypt192 == "Test program ..."){
			std::cout << "OK" << std::endl;
		}
		else{
			std::cout << "FAILED" << std::endl;
		}

		//Test the AES-256Bits algorithm
		std::cout << "AES 256 Bits : ";
		std::string key256 = ael::AES::GenerateKey(256);
		std::string encrypt256 = ael::AES::Encrypt("Test program ...", key256, 256);
		std::string decrypt256 = ael::AES::Decrypt(encrypt256, key256, 256);

		if(decrypt256 == "Test program ..."){
			std::cout << "OK" << std::endl;
		}
		else{
			std::cout << "FAILED" << std::endl;
		}

		//Test the MD5 algorithm
		std::cout << "MD5 : ";
		if(ael::Vector_UInt_To_Hex_String(ael::MD5("Hello world !")) == "67c18d060479c5d867c9b91c80edeb4c"){
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
