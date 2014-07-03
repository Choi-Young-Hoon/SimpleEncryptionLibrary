Advanced Encryption Library
===========================

MD5
---

MD5 is an algorithm that you can use to hash informations.

But, it's NOT SAFE to use it for cryptographic applications.
------------------------------------------------------------

How to use it ?

    //To find the hash of "Hello world !"
    std::vector<unsigned int> md5_hash = ael::MD5("Hello world !");
    
    //To show the hash in the console in hex format
    std::cout << "MD5 = " << std::hex << md5_hash[0] << md5_hash[1] << md5_hash[2] << md5_hash[3] << std::endl;
    
    //To convert the vector<unsigned int> to a string
    std::string md5_char = ael::Vector_UInt_To_String(md5_hash);
    
    //To convert the vector<unsigned int> to an Hex format in a string
    std::string md5_hex = ael::Vector_UInt_To_Hex_String(md5_hash);
