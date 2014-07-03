Advanced Encryption Library
===========================

LargeInt
--------

LargeInt is a specific class that provide a simple way to manage big numbers.

You can create a LargeInt like this :

    ael::LargeInt numberA, numberB(0x0125BDEF), numberC(numberB);
    unsigned char numberD[5] = {0x12, 0x52, 0xAB, 0xC2};
    unsigned int size = 5;
    ael::LargeInt numberE(numberD, size);
    
The arithmetic operations are :

	numberA += numberB;
	numberA = numberB + numberC;
	
	numberA -= numberB;
	numberA = numberA - numberC;
	
	numberA *= numberB;
	numberA = numberB * numberC;
	
	numberA %= numberB;
	numberA = numberB % numberC;
	
	numberA.Modular_Exp(numberB, numberC); //It's the equivalent to (numberA ^ numberB mod numberC)
	
You can also move all the bits to the right or the left :

    numberA.ToTheLeft();
	numberA.ToTheRight();
	
You can show the number :

    numberA.Show();
	
There are also two random number generator, but it's still a beta test :

    ael::LargeInt::Generer(unsigned int taille);
	ael::LargeInt::NumberGenerator(LargeInt& maxi, LargeInt& mini);
	
To get number.nombre[0] you can use :

    usnigned int number1 = number.GetFirst();
	