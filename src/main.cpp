/* ****************************************************************************
 *
 * Copyright 2013-2016 informaticien77
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
 * 				Test.cpp
 *
 * Author: informaticien77
 * Release date: 20th of February 2016
 *
 * ****************************************************************************
 */

#include "AEL.hpp"

int main(int argc, char *argv[]){

		std::cout << "Advanced Encryption Library Alpha 0.4.0" << std::endl << std::endl;
        
        if (argc <= 1){
            return 0;
        }
        
        if (!strcmp(argv[1], "encrypt") && argc >= 5){
            std::string argv2 = argv[2];
            if (!strcmp(argv[2], "AES")){
                ael::AES key(argv[3]);
                std::cout << key.Encrypt(argv[4]) << std::endl;
            }
            std::cout << "OK" << std::endl;
        }
        
        std::cout << "Done" << std::endl;
        std::getchar();
}