Advanced Encryption Library
===========================

What is it ?
------------

An Open Source C++ Library that provide a simple way to use encryption of many algorithms like Diffie-Hellman
key exchange, and the Advanced Encryption Standard (AES), with just a few lines of codes.

Implemented algorithms
----------------------

* AES-128
* AES-192
* AES-256
* MD5
* Miller-Rabin primality test
* Fermat primality test
* Euclide GCD

Compiling
---------

You have to use CMake to configure the compilation of the Library Project for your system.

You can decide to compile the test program. And also if you want a shared lib or a static version.
Also, you can compile Release or/and Debug version of it.

Then you have to compile it with a compiler like MinGW32, Visual C++ ...

Configuring
-----------

Depending on you IDE you have to link the library built, with your project. If you compile the shared Library
you should copy the DLL built at the same time, to the executable directory.

How to use it ?
---------------

All instructions are in the doc directory.

License (LGPL)
--------------

Copyright 2013, 2014 informaticien77

Advanced Encryption Library is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Advanced Encryption Library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

[See LGPL online](http://www.gnu.org/licenses/)