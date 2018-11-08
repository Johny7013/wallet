#include "wallet.h"

Wallet::Wallet() {
	operationsHistory.push_back(Operation(0));
}

Wallet::Wallet(unsigned long long n) {
	n *= UNITS_IN_B;
	balance = n;
	B_IN_CIRCULATION += n;
	operationsHistory.push_back(Operation(n));
}

Operation::Operation(unsigned int finalBalance) {
	this->finalBalance = finalBalance;
}

unsigned long long Operation::getUnits() {
	return finalBalance;
}

Operation Wallet::operator[] (int i) {
	return operationsHistory[i];
}
