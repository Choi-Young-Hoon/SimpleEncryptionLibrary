Simple Encryption Library
=========================

What is it ?
------------

An Open Source C++ Library that provide a simple way to use encryption of many algorithms like Diffie-Hellman
key exchange, and the Advanced Encryption Standard (AES), with just a few lines of codes.

Implemented algorithms
----------------------

* AES-128
* AES-192
* AES-256
* MD5 [RFC_1321] [RFC_6151]
* CRC-1 (bit parity)
* CRC-16 (IBM and MODBUS)
* CRC-32

In progress
-----------

* Miller-Rabin primality test
* Fermat primality test
* Euclide GCD

Build
-----

You have to use CMake to configure the compilation of the Library Project for your system.

You can decide to compile the test program. And also if you want a shared lib or a static version.
Also, you can compile Release or/and Debug version of it.

Then you have to compile it with a compiler like MinGW32, Visual C++ ...

### Linux

- ``` cmake ./CMakeLists.txt  ```
- ``` make  ```

Configuring
-----------

Depending on you IDE you have to link the library built, with your project. If you compile the shared Library
you should copy the DLL built at the same time, to the executable directory.

How to use it ?
---------------

All instructions are in the doc directory.

License
-------

This project is licensed under the terms of the MIT license.
