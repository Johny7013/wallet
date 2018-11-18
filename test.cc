// program to testowania, czy rzeczy dzialaja

#include <bits/stdc++.h>
#include "wallet.h"
using namespace std;

int main() {
	Wallet w0;
	cout << "Po pierwszej operacji w w0 portfelu bylo " << w0[0].getUnits() << " B" <<  endl;
	Wallet w(4);
	cout << "Po pierwszej operacji w w(4) portfelu bylo " << w[0].getUnits() << " B" <<  endl;

	// check if copy constuctor successfully forbidden
	//Wallet w1 = w0;
    // check if copy assignment successfully forbidden
	//w0 = w;

	// check move constuctor
    Wallet w2 = std::move(Wallet(42));
    cout << "Po pierwszej operacji w w2 portfelu bylo " << w2[0].getUnits() << " B" <<  endl;

    // check excpetion tooManyB
    //Wallet w3(22000000);

    // check Wallet(str)
    Wallet w4("34,67");
    cout << "Po pierwszej operacji w w4 portfelu bylo " << w4[0].getUnits() << " B" <<  endl;

    // check invalid_argument exception
    //Wallet w5("as,78");

    // check leading zeroes
    Wallet w6("000,78657");
    cout << "Po pierwszej operacji w w6 portfelu bylo " << w6[0].getUnits() << " B" <<  endl;


    // check Wallet( Wallet&& w1, Wallet&& w2)
    Wallet w7(Wallet(3), Wallet(7));
    for(int i = 0; i < 3; i++){
        cout << "Po " << i << "-tej operacji w w7 portfelu bylo " << w7[i].getUnits() << " B" <<  endl;
    }

    // check Wallet::fromBinary(str)
    Wallet w8 = Wallet::fromBinary("100000");
    cout << "Po pierwszej operacji w w8 portfelu bylo " << w8[0].getUnits() << " B" <<  endl;

    // check Operation to date
    cout << w8[0] <<  endl;

    
    // check move assignment 
	Wallet ww7(7);
	ww7 = Wallet(10);

	
	cout << "Po drugiej operacji w w7 portfelu bylo " << ww7[1].getUnits() << " B" << endl;
	
	// check operation out of bounds exception
	//cout << "Po trzeciej operacji w w7 portfelu bylo " << w7[2].getUnits() << " B" << endl;
	
	Wallet w8(8), w9(9);
	w8 += w9;
	
	w8 *= 3;
	
	w8 -= Wallet(5);
	
	w8 += Wallet(5);
	
	w8 += 3;
	w8 -= 3;
	w8.printHistory();
	
	Wallet w10(51);
	
	cout << (w10 == w8) << endl;
	cout << (Wallet(51) <= Wallet(50)) << endl;
	
	Wallet w11(3);
	Wallet w12 = w11 + Wallet(5);
	
	w12.printHistory(); 
	return 0;
}


