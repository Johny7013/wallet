#include "wallet.h"
#include <exception>
#include <regex>
#include <stdexcept>
#include <cstdlib>
#include <utility>
#include <iomanip>

using namespace std::rel_ops;

#ifdef NDEBUG
#define LOG(msg)
#else
#include <iostream>

using namespace std;

#define LOG(msg) \
    std::cout << "Line: " << __LINE__ << " " << (msg) << std::endl;
#endif



class TooManyBException: public std::exception

{
	virtual const char* what() const throw()
	{
		return "BajtekCoins upper limit exceeded (21e6 B)";
	}
} tooManyB;

class TooLittleBException: public std::exception
{
	virtual const char* what() const throw()
	{
		return "BajtekCoins lower limit exceeded (0 B)";
	}
} tooLittleB;

class OperationIndexOutOfBoundsException: public std::exception {
	virtual const char* what() const throw() {
		return "Operation index out of bounds";
	}
} invalidOperationIndex;

void Wallet::increaseBalance(unsigned long long delta) {
	if (delta > B_NOT_IN_CIRCULATION) {
		throw tooManyB;
	}

	balance += delta;
	B_NOT_IN_CIRCULATION -= delta;
}

void Wallet::decreaseBalance(unsigned long long delta) {
	if (delta > balance) {
		throw tooLittleB;
	}

	balance -= delta;
	B_NOT_IN_CIRCULATION += delta;
}

void Wallet::updateHistory() {
	operationsHistory.push_back(Operation(balance));
}

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

void Wallet::printHistory() {
	cout << endl;
	for (int i = 0; i < (int)operationsHistory.size(); i++) {
		cout << "After operation " << i << "   balance = " << operationsHistory[i].getUnits() << endl;
	}
	cout << endl;
}

// It is guaranteed by regex that exp <= 8
unsigned long long pow10(unsigned long exp){
    unsigned long long x = 1;
    for(int i = 0; i < exp; i++){
        x *= 10;
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

    std::cmatch parsedData;
    auto regexSuccess = std::regex_match(str, parsedData, regex);

    if(regexSuccess){
        std::string::size_type idx = 0;
        // integer part + mantissa
        return std::stoull(parsedData.str(1), &idx, 10) * units
                + std::stoull(parsedData.str(3), &idx, 10) * (units / pow10(parsedData.str(3).size()));
    }
    else{
        throw std::invalid_argument("Invalid argument passed to Wallet(str) constuctor");
    }

}

Wallet::Wallet(const char* str) {
    LOG("str constructor invoked")
    unsigned long long n = convertToUll(str, UNITS_IN_B);

    if(n > B_NOT_IN_CIRCULATION){
        throw tooManyB;
    }

    balance = n;
    B_NOT_IN_CIRCULATION -= n;
    updateHistory();
}

Wallet::Wallet(Wallet &&wallet)
    : balance(wallet.balance)
    , operationsHistory(std::move(wallet.operationsHistory)) {
    LOG("Move constructor invoked");
    updateHistory();
}

Wallet& Wallet::operator= (Wallet&& wallet) {
	// Checking if we assign the same object?
	LOG("Move assignment invoked");
	balance = wallet.balance;
	operationsHistory = std::move(wallet.operationsHistory);
	updateHistory();
	
	return *this;
}


Wallet& Wallet::operator+= (Wallet& wallet) {
	LOG("Operator += invoked");
	increaseBalance(wallet.balance);
	wallet.balance = 0;
	
	updateHistory();
	wallet.updateHistory();
	
	return *this;
}

Wallet& Wallet::operator+= (Wallet&& wallet) {
	LOG("Operator += invoked");
	increaseBalance(wallet.balance);
	wallet.balance = 0;
	
	updateHistory();
	wallet.updateHistory();
	
	return *this;
}

Wallet& Wallet::operator+= (unsigned long long n) {
	LOG("Operator += invoked");
	n *= UNITS_IN_B;
	increaseBalance(n);
	
	updateHistory();
	
	return *this;
}

Wallet& Wallet::operator-= (Wallet& wallet) {
	LOG("Operator -= invoked");
	decreaseBalance(wallet.balance);
	wallet.balance = 0;
	
	updateHistory();
	wallet.updateHistory();
	
	return *this;
}

Wallet& Wallet::operator-= (Wallet&& wallet) {
	LOG("Operator -= invoked");
	decreaseBalance(wallet.balance);
	wallet.balance = 0;
	
	updateHistory();
	wallet.updateHistory();
	
	return *this;
}

Wallet& Wallet::operator-= (unsigned long long n) {
	LOG("Operator -= invoked");
	n *= UNITS_IN_B;
	decreaseBalance(n);
	
	updateHistory();
	
	return *this;
}

Wallet& Wallet::operator*= (unsigned long long n) {
	LOG("Operator *= (int) invoked");
	
	// is n = 0 possible? If yes, we are in trouble
	increaseBalance(balance * (n - 1));
	updateHistory();
	
	return *this;
}


bool compareOperations(Operation op1, Operation op2){
    return op1 < op2;
}

Wallet::Wallet(Wallet&& w1, Wallet&& w2)
    : balance(w1.balance + w2.balance)
    , operationsHistory(std::move(w1.operationsHistory)) {
    LOG("Wallet( Wallet&& w1, Wallet&& w2) invoked");

    w1.balance = 0;
    w2.balance = 0;

    for(auto x: w2.operationsHistory){
        this->operationsHistory.push_back(x);
    }

    sort(this->operationsHistory.begin(), this->operationsHistory.end(), compareOperations);
    operationsHistory.push_back(Operation(balance));

    w2.operationsHistory.clear();
}

Wallet Wallet::fromBinary(const char *str) {
    std::string::size_type size = strlen(str);
    std::string::size_type idx = 0;

    unsigned long long x;

    try{
        x = std::stoull(str, &idx, 2);
        if(size != idx) {
            throw std::invalid_argument("");
        }
    }catch(...) {
        throw std::invalid_argument("Invalid argument passed to Wallet::fromBinary(str)");
    }

    return Wallet(x);
}


const Wallet Wallet::operator+ (const Wallet& wallet) const {
	return *this += wallet;
}

bool Wallet::operator== (const Wallet& wallet) {
	return balance == wallet.balance;
}

bool Wallet::operator!= (const Wallet& wallet) {
	return balance != wallet.balance;
}

bool Wallet::operator< (const Wallet& wallet) {
	return balance < wallet.balance;
}

bool Wallet::operator<= (const Wallet& wallet) {
	return balance <= wallet.balance;
}

bool Wallet::operator>= (const Wallet& wallet) {
	return balance >= wallet.balance;
}

bool Wallet::operator> (const Wallet& wallet) {
	return balance > wallet.balance;
} 


Operation::Operation(unsigned long long finalBalance) {
	this->finalBalance = finalBalance;
	this->time = std::time(nullptr);
}

unsigned long long Operation::getUnits(){
	return finalBalance;
}

Operation Wallet::operator[] (int i) {
	if (i >= operationsHistory.size()) {
		throw invalidOperationIndex;
	} 
	return operationsHistory[i];
}

std::ostream& operator<< (std::ostream& os, const Operation& op)
{
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    os << "Wallet balance is " << op.finalBalance << std::put_time(&tm, " B after operation made at day %F");
    return os;
}
