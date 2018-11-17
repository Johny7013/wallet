#include "wallet.h"
#include <exception>

#ifdef NDEBUG
#define LOG(msg)
#else
#include <iostream>
#define LOG(msg) \
    std::cout << "Line: " << __LINE__ << " " << (msg) << std::endl;
#endif

class CustomException: public std::exception
{
	virtual const char* what() const throw()
	{
		return "B in circulation out of bounds";
	}
} tooManyB;

Wallet::Wallet() {
    LOG("Default constructor invoked");
	operationsHistory.push_back(Operation(0));
}

Wallet::Wallet(unsigned long long n) {
    LOG("n constructor invoked");
	n *= UNITS_IN_B;

	if(n > B_NOT_IN_CIRCULATION){
		throw tooManyB;
	}

	balance = n;
	B_NOT_IN_CIRCULATION -= n;
	operationsHistory.push_back(Operation(n));
}

Wallet::Wallet(Wallet &&wallet)
    : balance(wallet.balance)
    , operationsHistory(std::move(wallet.operationsHistory)) {
    LOG("Move constructor invoked");
    operationsHistory.push_back(Operation(balance));
}

Operation::Operation(unsigned int finalBalance) {
	this->finalBalance = finalBalance;
	this->time = std::time(nullptr);
}

unsigned long long Operation::getUnits() {
	return finalBalance;
}

Operation Wallet::operator[] (int i) {
	return operationsHistory[i];
}
