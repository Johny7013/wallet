// program to testowania, czy rzeczy dzialaja

#include <bits/stdc++.h>
#include "wallet.h"
using namespace std;

int main() {
	Wallet w0;
	cout << "Po pierwszej operacji w portfelu bylo " << w0[0].getUnits() << " B" <<  endl;
	Wallet w(4);
	cout << "Po pierwszej operacji w portfelu bylo " << w[0].getUnits() << " B" <<  endl;
	
	return 0;
}


