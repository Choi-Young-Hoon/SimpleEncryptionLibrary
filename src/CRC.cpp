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
        crc_hash = 0x0;
        return;
    }

    uint8_t compute_hash = data[0];
    for (int i = 1; i < data.size(); i++){
        compute_hash ^= data[i];
    }

    while(compute_hash > 0){
        crc_hash ^= compute_hash & 0x01;
        compute_hash >>= 1;
    }
 }

 bool sel::CRC1::result(void){
    return crc_hash;
 }

 uint16_t sel::CRC16::reversed16(uint16_t data){
    uint16_t r_data = 0x0000;

    for(uint8_t i = 0; i < 16; i++){
        r_data |= ((data >> (15-i)) & 0x0001) << i;
    }

    return r_data;
 }

 uint8_t sel::CRC16::reversed8(uint8_t data){
    uint8_t r_data = 0x00;

    for(uint8_t i = 0; i < 8; i++){
        r_data |= ((data >> (7-i)) & 0x01) << i;
    }

    return r_data;
 }

 sel::CRC16::CRC16(const std::string data, int type){
    switch (type)
    {
    case sel::CRC16::CRC16_IBM:
        crc_hash = crc_gen(data, 0x8005, 0x0000, 0x0000, true, true);
        break;
    case sel::CRC16::CRC16_MODBUS:
        crc_hash = crc_gen(data, 0x8005, 0xFFFF, 0x0000, true, true);
        break;
    }
 }

 uint16_t sel::CRC16::crc_gen(const std::string data, uint16_t polynomial,
    const uint16_t initial_value, const uint16_t final_value,
    const bool input_reflected, const bool result_reflected){

    std::string current_data = data;
    uint16_t crc = initial_value;

    if(!input_reflected){
        std::reverse(current_data.begin(), current_data.end());

        for(uint16_t i = 0; i < current_data.size(); i++){
            current_data[i] = sel::CRC16::reversed8(current_data[i]);
        }

        std::cout << std::hex << polynomial << std::endl;
    }
    else{
        polynomial = sel::CRC16::reversed16(polynomial);
    }

    for(uint16_t i = 0; i < current_data.size(); i++){
        crc ^= current_data[i];
        for(uint8_t j = 0; j < 8; j++){
            if(crc & 0x0001 > 0){
                crc = (crc >> 1) ^ polynomial;
            }
            else{
                crc >>= 1;
            }
        }
    }

    if(!result_reflected){
        return sel::CRC16::reversed16(crc) ^ final_value;
    }
    else{
        return crc ^ final_value;
    }
 }

 uint16_t sel::CRC16::result(void){
    return crc_hash;
 }

 sel::CRC32::CRC32(const std::string data, int type){
    switch(type){
    case sel::CRC32::CRC32_NORMAL:
        crc_hash = crc_gen(data, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true);
        break;
    }
 }

uint32_t sel::CRC32::crc_gen(const std::string data, uint32_t polynomial,
    const uint32_t initial_value, const uint32_t final_value,
    const bool input_reflected, const bool result_reflected){

    std::string current_data = data;
    uint32_t crc = initial_value;

    if(!input_reflected){
        std::reverse(current_data.begin(), current_data.end());

        for(uint32_t i = 0; i < current_data.size(); i++){
            current_data[i] = sel::CRC32::reversed8(current_data[i]);
        }

        std::cout << std::hex << polynomial << std::endl;
    }
    else{
        polynomial = sel::CRC32::reversed32(polynomial);
    }

    for(uint16_t i = 0; i < current_data.size(); i++){
        crc ^= current_data[i];
        for(uint8_t j = 0; j < 8; j++){
            if(crc & 0x0001 > 0){
                crc = (crc >> 1) ^ polynomial;
            }
            else{
                crc >>= 1;
            }
        }
    }

    if(!result_reflected){
        return sel::CRC32::reversed32(crc) ^ final_value;
    }
    else{
        return crc ^ final_value;
    }
 }

 uint32_t sel::CRC32::reversed32(uint32_t data){
    uint32_t r_data = 0x0000;

    for(uint8_t i = 0; i < 32; i++){
        r_data |= ((data >> (31-i)) & 0x0001) << i;
    }

    return r_data;
 }

 uint8_t sel::CRC32::reversed8(uint8_t data){
    uint8_t r_data = 0x00;

    for(uint8_t i = 0; i < 8; i++){
        r_data |= ((data >> (7-i)) & 0x01) << i;
    }

    return r_data;
 }

 uint32_t sel::CRC32::result(void){
    return crc_hash;
 }
