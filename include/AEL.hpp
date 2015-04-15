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
 * 				AEL.hpp
 *
 * Author: informaticien77
 * Release date: 27th of June 2014
 *
 * ****************************************************************************
 */

#ifndef AEL_HPP
#define AEL_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>
#include <vector>
#include <iomanip>
#include <sstream>

namespace ael
{
	class AES
	{
	public:
	    AES();
	    AES(std::string key);

		void GenerateKey(int keybits = 128);

		std::string Encrypt(std::string plaintext);
		std::string Decrypt(std::string ciphertext);

    private:
        std::string aes_key;

	};

	class LargeInt
	{
	public:
		LargeInt();
		LargeInt(std::vector<unsigned int> a);
		LargeInt(std::string a);
		LargeInt(unsigned char a[], unsigned int size);
		LargeInt(LargeInt const& a);
		LargeInt(unsigned int a);
		~LargeInt();

		const void Show();
		std::string as64String(void);
		std::vector<unsigned int> asVector(void);

		void RussianMultiplication(LargeInt const& a, LargeInt const& b);
		void Modular_Exp(LargeInt& exposant, LargeInt& modulo);
		void NumberGenerator(LargeInt& maxi, LargeInt& mini);

		void BitGenerator(unsigned int lenght);
		bool FermatPrimality(void);
		LargeInt EuclideAlgoPGCD(LargeInt& b);
		bool MillerRabinPrimality(unsigned int iterations);

		void ToTheRight();
		void ToTheLeft();
		void Generate(unsigned int taille);
		unsigned int GetFirst();
		unsigned int size();

		bool operator==(LargeInt const& a);
		bool operator!=(LargeInt const& a);
		bool operator<(LargeInt const& a);
		bool operator<=(LargeInt const& a);
		bool operator>(LargeInt const& a);
		bool operator>=(LargeInt const& a);

		LargeInt& operator=(LargeInt const& a);

		void operator+=(LargeInt const& a);
		LargeInt& operator+(LargeInt const& a);

		void operator-=(LargeInt const& a);
		LargeInt& operator-(LargeInt const& a);

		void operator*=(LargeInt const& a);
		LargeInt& operator*(LargeInt const& a);

		void operator%=(LargeInt const& a);
		LargeInt& operator%(LargeInt const& a);

	private:
		std::vector<unsigned int> nombre;
	};

	class MD5
	{
    public:
        MD5(const std::string text);

        std::string asString(void);
        std::string asHexString(void);
        std::vector<unsigned int> asVector(void);
    private:
        std::vector<unsigned int> text_digest;
	};
}

#endif
