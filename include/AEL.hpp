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

#ifndef AEL_H
#define AEL_H

#include <string>
#include <fstream>

namespace ael
{
	class AES
	{
	public:

		static std::string GenerateKey(int keybits = 128);

		static std::string Encrypt(std::string plaintext, std::string key, int keybits = 128);

		static std::string Decrypt(std::string ciphertext, std::string key, int keybits = 128);

	};
	/*class RSA
	{
	public:

		static bool GenerateKeys(unsigned long int digitCount, std::string *moduluskeys, std::string *privatexponent, std::string *publicexponent, unsigned long int precisionOfPrimality = 3);

		static std::string Encrypt(std::string plaintext, std::string keymod, std::string keyexp);

		static std::string Decrypt(std::string ciphertext, std::string keymod, std::string keyexp);

	};*/
    /*class HASH
    {
    public:

        static std::string MD5(const std::string text);

    };*/
}

#endif
