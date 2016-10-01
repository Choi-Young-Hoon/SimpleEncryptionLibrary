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

#include "SEL.hpp"

unsigned int md5_rotate_left(unsigned int x, unsigned int n) {
  return ((x << n) | (x >> (32-n)));
}

sel::MD5::MD5(const std::string text){
    //Note: All variables are unsigned 32 bit and wrap modulo 2^32 when calculating
    std::vector<unsigned int> message;
    unsigned int lengthMessage[2];

    if(text.size() > 0){
        message.resize(ceil(text.size() / 4.0));

        unsigned int tempo = 0x00;
        for(unsigned int z = 0; z < message.size(); z++){
            message[z] = 0x00;
            for(unsigned int y = 0; (y < 4) && ((y+4*z) < text.size()); y++){
                tempo = text[y+4*z];
                message[z] = (message[z] | (tempo <<= y*8));
            }
        }

        unsigned int long long length = (text.size() * 8) & 0xFFFFFFFFFFFFFFFF;
        lengthMessage[0] = static_cast<unsigned int>(length & 0xFFFFFFFF);
        lengthMessage[1] = static_cast<unsigned int>(length >>= 32);
    }
    else{
        message.resize(1);
        message[0] = 0x00;
        lengthMessage[0] = 0x00;
        lengthMessage[1] = 0x00;
    }

    //r specifies the per-round shift amounts
    unsigned int r[64] = {
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
        5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

    unsigned int k[64] = { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee
        ,0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501
        ,0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be
        ,0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821
        ,0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa
        ,0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8
        ,0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed
        ,0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a
        ,0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c
        ,0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70
        ,0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05
        ,0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665
        ,0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039
        ,0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1
        ,0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1
        ,0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };

    //Initialize variables
    unsigned int h0 = 0x67452301, h1 = 0xefcdab89, h2 = 0x98badcfe, h3 = 0x10325476;

    //Pre-processing: adding a single 1 bit
    unsigned int test = 0x80, mes = 0xff;
    while((mes & message[message.size()-1]) != 0){
        test <<= 8;
        mes <<= 8;
    }

    if(test == 0){
         message.push_back(0x80);
    }
    else{
        message[message.size()-1] = (message[message.size()-1] | test);
    }

    //Pre-processing: padding with zeros
    while((message.size() % 16) != 14){
        message.push_back(0x00);
    }

    message.push_back(lengthMessage[0]);

    message.push_back(lengthMessage[1]);

    unsigned int a, b, c, d, f, temp, g = 0, w[16];

    //Process the message in successive 512-bit chunks
    for(unsigned int j = 0; j < (message.size() / 16); j++){

        for(unsigned int m = 0; m < 16; m++){
            w[m] = message[m+j*16];
        }

        //Initialize hash value for this chunk
        a = h0;
        b = h1;
        c = h2;
        d = h3;

        //Main loop
        for(unsigned int l = 0; l < 64; l++){
            if((l >= 0) && (l <= 15)){
                f = ((b & c) | ((~b) & d)); //Round 1
                g = l;
            }
            else if((l >= 16) && (l <= 31)){
                f = ((d & b) | ((~d) & c)); //Round 2
                g = ((5*l + 1) % 16);
            }
            else if((l >= 32) && (l <= 47)){
                f = ((b ^ c) ^ d); //Round 3
                g = ((3*l + 5) % 16);
            }
            else if((l >= 48) && (l <= 63)){
                f = (c ^ (b | (~d))); //Round 4
                g = ((7*l) % 16);
            }

            temp = d;
            d = c;
            c = b;
            b = (md5_rotate_left((a + f + k[l] + w[g]), r[l]) + b);
            a = temp;

        }

         //Add result to precedent block
         h0 = h0 + a;
         h1 = h1 + b;
         h2 = h2 + c;
         h3 = h3 + d;

    }

    unsigned int digest[4];
    digest[0] = ((h0>>24)&0xff) | // move byte 3 to byte 0
                    ((h0<<8)&0xff0000) | // move byte 1 to byte 2
                    ((h0>>8)&0xff00) | // move byte 2 to byte 1
                    ((h0<<24)&0xff000000); // byte 0 to byte 3

    digest[1] = ((h1>>24)&0xff) | // move byte 3 to byte 0
                    ((h1<<8)&0xff0000) | // move byte 1 to byte 2
                    ((h1>>8)&0xff00) | // move byte 2 to byte 1
                    ((h1<<24)&0xff000000); // byte 0 to byte 3

    digest[2] = ((h2>>24)&0xff) | // move byte 3 to byte 0
                    ((h2<<8)&0xff0000) | // move byte 1 to byte 2
                    ((h2>>8)&0xff00) | // move byte 2 to byte 1
                    ((h2<<24)&0xff000000); // byte 0 to byte 3

    digest[3] = ((h3>>24)&0xff) | // move byte 3 to byte 0
                    ((h3<<8)&0xff0000) | // move byte 1 to byte 2
                    ((h3>>8)&0xff00) | // move byte 2 to byte 1
                    ((h3<<24)&0xff000000); // byte 0 to byte 3

    text_digest.resize(4);

    text_digest[0] = digest[0];
    text_digest[1] = digest[1];
    text_digest[2] = digest[2];
    text_digest[3] = digest[3];

}

std::string sel::MD5::asString(){
    std::string result = "";
    for(unsigned int i = 0; i < text_digest.size(); i++){
        result += (text_digest[i] & 0xFF);
        result += ((text_digest[i] >>= 8) & 0xFF);
        result += ((text_digest[i] >>= 16) & 0xFF);
        result += ((text_digest[i] >>= 24) & 0xFF);
    }
    return result;
}

std::string sel::MD5::asHexString(){
    std::ostringstream ss;
    for(unsigned int i = 0; i < text_digest.size(); i++){
        ss << std::setfill('0') << std::setw(8) << std::hex << text_digest[i];
    }
    return ss.str();
}

std::vector<unsigned int> sel::MD5::asVector(){
    std::vector<unsigned int> result;
    result = text_digest;
    return result;
}
