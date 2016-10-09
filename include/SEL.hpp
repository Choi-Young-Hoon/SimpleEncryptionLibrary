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
        enum
        {
            AES128 = 128,
            AES192 = 192,
            AES256 = 256
        };

	    AES();
	    AES(std::string key);

		void GenerateKey(int type = AES::AES128);

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
		LargeInt(unsigned char a[], uint16_t size);
		LargeInt(LargeInt const& a);
		LargeInt(unsigned int a);
		~LargeInt();

		void Show() const;
		std::string as64String(void);
		std::vector<uint32_t> asVector(void);

		LargeInt mul_russian(LargeInt const& b);
		void Modular_Exp(LargeInt& exposant, LargeInt& modulo);
		LargeInt mul_karatsuba(LargeInt const& b);

		void NumberGenerator(LargeInt& maxi, LargeInt& mini);
		void BitGenerator(unsigned int lenght);

		bool FermatPrimality(void);
		LargeInt EuclideAlgoPGCD(LargeInt& b);
		bool MillerRabinPrimality(unsigned int iterations);

		void ToTheRight();
		void ToTheLeft();
		void Generate(unsigned int taille);
		uint32_t GetFirst();

		uint32_t size_bits() const;
		uint32_t size() const;

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

		void operator<<=(const uint32_t shifts);
		LargeInt operator<<(const uint32_t shifts);

		void operator>>=(const uint32_t shifts);
		LargeInt operator>>(const uint32_t shifts);

		void operator&=(LargeInt const& y);
		LargeInt operator&(LargeInt const& y);

		void operator|=(LargeInt const& y);
		LargeInt operator|(LargeInt const& y);

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
        std::vector<uint32_t> asVector(void);

    private:
        std::vector<uint32_t> text_digest;
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
        bool crc_hash;
	};

	/*
	 * Class CRC16 : Cyclic Redundancy Check 16 bits
	 */
	class CRC16
	{
	public:
        enum
        {
            CRC16_IBM = 0,
            CRC16_MODBUS = 1
        };

        CRC16(const std::string data, int type = CRC16::CRC16_IBM);
        uint16_t crc_gen(std::string data, const uint16_t polynomial,
            const uint16_t initial_value, const uint16_t final_value,
            const bool input_reflected, const bool result_reflected);
        uint16_t result(void);
        uint16_t reversed16(uint16_t data);
        uint8_t reversed8(uint8_t data);

    private:
        uint16_t crc_hash;
	};

	/*
	 * Class CRC32 : Cyclic Redundancy Check 32 bits
	 */
    class CRC32
    {
    public:
        enum
        {
            CRC32_NORMAL = 0
        };

        CRC32(const std::string data, int type = CRC32::CRC32_NORMAL);
        uint32_t crc_gen(std::string data, const uint32_t polynomial,
            const uint32_t initial_value, const uint32_t final_value,
            const bool input_reflected, const bool result_reflected);
        uint32_t result(void);
        uint32_t reversed32(uint32_t data);
        uint8_t reversed8(uint8_t data);

    private:
        uint32_t crc_hash;
    };

    void randinit(void);
	LargeInt Karatsuba(LargeInt& N, LargeInt& M);
}

#endif
