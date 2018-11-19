// program to testowania, czy rzeczy dzialaja

#include <bits/stdc++.h>
#include "wallet.h"
using namespace std;

int main() {
	Wallet w1(1), w2(2);
	Wallet w3 = w1 * 42;
	Wallet w4 = 42 * w2;
	Wallet w5 = Wallet(1) * 42;
	Wallet w6 = 42 * Wallet(2);
	Wallet w7 = Wallet(3) *= 42;
    w3.printHistory();
    w4.printHistory();
    w5.printHistory();
    w6.printHistory();
    w7.printHistory();
	
	
	
    Wallet ww1(1), ww2(2);
    //Wallet suma1 = ww1 + Wallet(1); // błąd kompilacji
    Wallet suma2 = Wallet(2) + ww2; // OK, w ww2 jest 0 B po operacji
                                   // i jeden nowy wpis w historii,
                                   // a w suma2 jest w2.getUnits() + 2 B.
                                   // Historia operacji powstałego obiektu
                                   // zależy od implementacji.
    //Wallet suma3 = suma1 + suma2;  // błąd kompilacji
    Wallet suma4 = Wallet(1) + Wallet(2);  // OK, suma4 ma dwa wpisy
                                           // w historii i 3 B
                        
    suma2.printHistory();
    suma4.printHistory();
    ww2.printHistory();                                       
	return 0;
}


