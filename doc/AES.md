Advanced Encryption Library
===========================

AES
---

You can use the Advanced Encryption Standart algorithm by using 3 different functions provide by AEL.

*   `ael::AES::GenerateKey(int keybits);`
This generate a pseudo-random key to use with AES. You can specify the number of key-bits. Those which are supported : 128, 192 and 256 bits.

*   `ael::AES::Encrypt(std::string plaintext, std::string key, int keybits);`
This encrypt the plaintext data with the key. You must specify a key of 128, 192 or 256 bits-length exactly.

*   `ael::AES::Decrypt(std::string text, std::string key, int keybits);`
This is the inverted function of Encrypt. You must specify the key and its lenght in bits. Also the text to Decrypt.

General example :

    #include <iostream>
    #include "AEL.hpp"
    
    int main(){
        std::string key = ael::AES::GenerateKey(128);
        std::string encrypt = ael::AES::Encrypt("Test program ...", key, 128);
        std::string decrypt = ael::AES::Decrypt(encrypt, key, 128);
        if(decrypt == "Test program ..."){
           std::cout << "It's working !" << std::endl;
        else{
           std::cout << "Fail" << std::endl;
        }
        return 0;
    }