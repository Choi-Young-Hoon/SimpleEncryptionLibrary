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

#ifndef SEL_HPP
#define SEL_HPP

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
#include <algorithm>

namespace sel
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
		LargeInt(std::string a);
		LargeInt(std::vector<uint32_t> &a);
		LargeInt(unsigned char a[], unsigned int size);
		LargeInt(LargeInt const& a);
		LargeInt(unsigned int a);
		~LargeInt();

		const void Show();
		std::string as64String(void);
		std::vector<uint32_t> asVector(void);

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
		uint_fast32_t size();

		bool getbit(const uint32_t position);
		void setbit(const bool bit, const uint32_t position);

		bool operator==(LargeInt const& a);
		bool operator!=(LargeInt const& a);
		bool operator<(LargeInt const& a);
		bool operator<=(LargeInt const& a);
		bool operator>(LargeInt const& a);
		bool operator>=(LargeInt const& a);

		LargeInt& operator=(LargeInt const& a);

		void operator+=(LargeInt const& a);
		LargeInt operator+(LargeInt const& a);

		void operator-=(LargeInt const& a);
		LargeInt operator-(LargeInt const& a);

		void operator*=(LargeInt const& a);
		LargeInt operator*(LargeInt const& a);

		void operator%=(LargeInt const& a);
		LargeInt operator%(LargeInt const& a);

	private:
		std::vector<uint32_t> nombre;
	};

	/*
	 * Class MD5 : Message Digest 5
	 */
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

	/*
	 * Class CRC1 : Cyclic Redundancy Check 1 bit
	 */
	class CRC1
	{
	public:
        CRC1(const std::string data);
        bool result(void);
    private:
        bool crc1_hash;
	};

    void randinit(void);
	LargeInt Karatsuba(LargeInt& N, LargeInt& M);
}

#endif
