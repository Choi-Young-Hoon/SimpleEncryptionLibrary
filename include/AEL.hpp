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
#include <math.h>
#include <vector>
#include <iomanip>

namespace ael
{
	class AES
	{
	public:

		static std::string GenerateKey(int keybits = 128);

		static std::string Encrypt(std::string plaintext, std::string key, int keybits = 128);

		static std::string Decrypt(std::string ciphertext, std::string key, int keybits = 128);

	};
    /*class HASH
    {
    public:

        static std::string MD5(const std::string text);

    };*/
	class LargeInt
	{

	public:
		LargeInt();
		LargeInt(std::string a);
		LargeInt(LargeInt const& a);
		LargeInt(unsigned int a);
		~LargeInt();

		const void Show();

		void MultiplicationRusse(LargeInt const& a, LargeInt const& b);
		void Modular_Exp(LargeInt& exposant, LargeInt& modulo);
		void NumberGenerator(LargeInt& maxi, LargeInt& mini);

		void Decalage_Droite();
		void Decalage_Gauche();
		void Generer(unsigned int taille);
		unsigned int GetFirst();

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
	class Algo
	{
	public:
		static LargeInt BitGenerator(unsigned int lenght);
		
		static bool FermatPrimality(LargeInt& b);
		static LargeInt EuclideAlgoPGCD(LargeInt& a, LargeInt& b);
		static bool MillerRabinPrimality(LargeInt& n0, unsigned int iterations);
	};
}

#endif
