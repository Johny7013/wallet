#ifndef _WALLET_H_
#define _WALLET_H_

#include <vector>
#include <ctime>

class Operation {
	private:
		unsigned long long finalBalance;
		time_t time;

	public:
        Operation(unsigned int finalBalance);
		unsigned long long getUnits();
	
};

class Wallet {
	private: 
		static const unsigned int UNITS_IN_B = 100'000'000;
		inline static unsigned long long B_NOT_IN_CIRCULATION = static_cast<unsigned long long>(21e14);
		unsigned long long balance = 0;
		
		std::vector<Operation> operationsHistory;
	
	public:
        Wallet();
		Wallet(unsigned long long n);
		// copy constructor explicitly forbidden
		Wallet(const Wallet& wallet) = delete;
        // copy assignment explicitly forbidden
		Wallet& operator= (const Wallet& wallet) = delete;
		Wallet(Wallet&& wallet);
		Operation operator[] (int i);
};




#endif // _WALLET_H_
