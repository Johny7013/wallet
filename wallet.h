#ifndef _WALLET_H_
#define _WALLET_H_

#include <vector>

class Operation {
	private:
		unsigned long long finalBalance;

	public:
        Operation(unsigned int finalBalance);
		unsigned long long getUnits();
	
};

class Wallet {
	private: 
		static const unsigned int UNITS_IN_B = 100'000'000;
		inline static unsigned int B_IN_CIRCULATION = 0;
		unsigned long long balance = 0;
		
		std::vector<Operation> operationsHistory;
	
	public:
        Wallet();
		Wallet(unsigned long long n);
		Operation operator[] (int i);
};




#endif // _WALLET_H_
