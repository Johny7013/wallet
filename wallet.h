#ifndef _WALLET_H_
#define _WALLET_H_

#include <vector>
#include <ctime>

class Operation {
	private:
		unsigned long long finalBalance;
		time_t time;

	public:
        Operation(unsigned long long finalBalance);
		unsigned long long getUnits();
	
};

class Wallet {
	private: 
		static const unsigned long long UNITS_IN_B = 100'000'000;
		inline static unsigned long long B_NOT_IN_CIRCULATION = static_cast<unsigned long long>(21e14);
		unsigned long long balance = 0;
		
		std::vector<Operation> operationsHistory;
	
		void updateHistory();
		void increaseBalance(unsigned long long delta);
		void decreaseBalance(unsigned long long delta);
	
	public:
        Wallet();
		Wallet(unsigned long long n);
		Wallet(const char* str);
		// copy constructor explicitly forbidden
		Wallet(const Wallet& wallet) = delete;
        // copy assignment explicitly forbidden
		Wallet& operator= (const Wallet& wallet) = delete;
		// move assignment allowed
		Wallet& operator= (Wallet&& wallet);
		Wallet(Wallet&& wallet);
		
		Wallet& operator+= (Wallet& wallet);
		Wallet& operator+= (Wallet&& wallet);
		Wallet& operator+= (unsigned long long n);
		Wallet& operator*= (unsigned long long n);
		Wallet& operator-= (Wallet& wallet);
		Wallet& operator-= (Wallet&& wallet);
		Wallet& operator-= (unsigned long long n);
		
		const Wallet operator+ (const Wallet& wallet) const;
		
		bool operator== (const Wallet& wallet); 
		bool operator!= (const Wallet& wallet);
		bool operator< (const Wallet& wallet);
		bool operator<= (const Wallet& wallet);
		bool operator> (const Wallet& wallet);
		bool operator>= (const Wallet& wallet);
		
		Operation operator[] (int i);
		
		
		// temporary, delete before submitting 
		void printHistory();
};




#endif // _WALLET_H_
