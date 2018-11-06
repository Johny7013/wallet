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
		static const unsigned int UNITS_IN_B = 100000000; 
		unsigned long long balance;
		
		std::vector<Operation> operationsHistory;
	
	public:
		Wallet(unsigned long long n);
		Operation operator[] (int i);
};




#endif // _WALLET_H_
