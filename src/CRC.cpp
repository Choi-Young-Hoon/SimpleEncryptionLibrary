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

 sel::CRC1::CRC1(const std::string data){
    if(data.size() == 0){
        crc1_hash = 0x0;
        return;
    }

    uint8_t compute_hash = data[0];
    for (int i = 1; i < data.size(); i++){
        compute_hash ^= data[i];
    }

    while(compute_hash > 0){
        crc1_hash ^= compute_hash & 0x01;
        compute_hash >>= 1;
    }
 }

 bool sel::CRC1::result(void){
    return crc1_hash;
 }
