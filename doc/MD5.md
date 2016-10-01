Simple Encryption Library
=========================

MD5
---

MD5 is an algorithm that you can use to hash informations.

But, it's NOT SAFE to use it for cryptographic applications.
------------------------------------------------------------

How to use it ?

    //To find the hash of "Hello world !"
    sel::MD5 md5_hash("Hello world !");
    
    //To convert the MD5 hash to a string
    std::string md5_char = md5_hash.asString();
    
    //To convert the MD5 hash to an Hex format in a string
    std::string md5_hex = md5_hash.asHexString();
