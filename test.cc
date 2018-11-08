// program to testowania, czy rzeczy dzialaja

#include <bits/stdc++.h>
#include "wallet.h"
using namespace std;

int main() {
	Wallet w0;
	cout << "Po pierwszej operacji w portfelu bylo " << w0[0].getUnits() << " B" <<  endl;
	Wallet w(4);
	cout << "Po pierwszej operacji w portfelu bylo " << w[0].getUnits() << " B" <<  endl;

	// check if copy constuctor successfully forbidden
	//Wallet w1 = w0;
    // check if copy assignment successfully forbidden
	//w0 = w;

	// check move constuctor
    Wallet w2 = std::move(Wallet(42));
    cout << "Po pierwszej operacji w portfelu bylo " << w2[0].getUnits() << " B" <<  endl;
	
	return 0;
}


