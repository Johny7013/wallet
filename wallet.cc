#include "wallet.h"
#include <exception>
#include <regex>
#include <stdexcept>
#include <cstdlib>

#ifdef NDEBUG
#define LOG(msg)
#else
#include <iostream>
#define LOG(msg) \
    std::cout << "Line: " << __LINE__ << " " << (msg) << std::endl;
#endif

class OutOfBondsException: public std::exception
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

long long pow(long long base, unsigned long exp){
    long long x = 1;
    for(int i = 0; i < exp; i++){
        x *= base;
    }
    return x;
}

unsigned long long convertToUll(const char* str, unsigned long long units){
    static const std::regex regex(
            // integer part
            R"(^(?:\s*)(0*[1-9]?[0-9]{0,7}))"

            // mantissa
            R"(([,.]([0-9]{0,8}))?(?:\s*)$)"
            );

    const std::string s(str);
    std::smatch parsedData;
    auto regexSuccess = std::regex_match(s, parsedData, regex);

    if(regexSuccess){
        std::string::size_type sz = 0;
        // integer part + mantissa
        return std::stoull(parsedData.str(1), &sz, 10) * units
                + std::stoull(parsedData.str(3), &sz, 10) * (units / pow(10, parsedData.str(3).size()));
    }
    else{
        throw std::invalid_argument("Invalid argument passed to Wallet(str) constuctor");
    }

}

Wallet::Wallet(const char* str) {
    unsigned long long n = convertToUll(str, UNITS_IN_B);

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

Operation::Operation(unsigned long long finalBalance) {
	this->finalBalance = finalBalance;
	this->time = std::time(nullptr);
}

unsigned long long Operation::getUnits() {
	return finalBalance;
}

Operation Wallet::operator[] (int i) {
	return operationsHistory[i];
}
