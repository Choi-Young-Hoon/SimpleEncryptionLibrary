Advanced Encryption Library
===========================

AES
---

You can use the Advanced Encryption Standart algorithm by using 3 different functions provide by AEL.

*   `ael::AES key_aes;`

*   `key_aes.GenerateKey(int keybits);`
This generate a pseudo-random key to use with AES. You can specify the number of key-bits. Those which are supported : 128, 192 and 256 bits.

*   `key_aes.Encrypt(std::string plaintext);`
This encrypt the plaintext data with the key. You must specify a key of 128, 192 or 256 bits-length exactly.

*   `key_aes.Decrypt(std::string text);`
This is the inverted function of Encrypt. You must specify the key and its lenght in bits. Also the text to Decrypt.

General example :

    #include <iostream>
    #include "AEL.hpp"
    
    int main(){
		ael::AES key_aes;
        key_aes.GenerateKey(128);
        std::string encrypt = key_aes.Encrypt("Test program ...");
        std::string decrypt = key_aes.Decrypt(encrypt);
		
        if(decrypt == "Test program ..."){
           std::cout << "It's working !" << std::endl;
        else{
           std::cout << "Fail" << std::endl;
        }
        return 0;
    }