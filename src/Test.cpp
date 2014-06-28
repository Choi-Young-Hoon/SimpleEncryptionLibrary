#include <iostream>
#include "AEL.hpp"

bool TestDiffieHellman(void){
    ael::LargeInt p(0), g(0), A(0), B(0), a(0), b(0), s1(0), s2(0);

    p = ael::Algo::BitGenerator(128);

    while(!ael::Algo::FermatPrimality(p)){
    //while(!MillerRabinPrimality(p, 6)){
        p = ael::Algo::BitGenerator(128);
        p.Show();
    }
    std::cout << std::endl << "Prime Number !" << std::endl << std::endl;

    std::cout << " P = ";
    p.Show();

    g = ael::Algo::BitGenerator(64);

    std::cout << " G = ";
    g.Show();

    a = ael::Algo::BitGenerator(384);

	std::cout << "Press a touch ..." << std::endl;
    std::getchar();

    b = ael::Algo::BitGenerator(384);
    A = g;
    A.Modular_Exp(a, p);
    B = g;
    B.Modular_Exp(b, p);
    s1 = B;
    s1.Modular_Exp(a, p);
    s2 = A;
    s2.Modular_Exp(b, p);

    std::cout << " s1 = ";
    s1.Show();
    std::cout << " s2 = ";
    s2.Show();

    if(s1 == s2){
        return true;
    }
    else{
        return false;
    }
}

int main(){

		ael::LargeInt a(0x526348);
		a.Show();
		TestDiffieHellman();
        std::cout << "Diffie Hellman : OK" << std::endl << "Press a touch to quit ..." << std::endl;
		std::getchar();

        return 0;

}
