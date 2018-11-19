#ifndef _WALLET_H_
#define _WALLET_H_

#include <vector>
#include <ctime>
#include <iostream>

using namespace std::rel_ops;

class Operation {
	private:
		unsigned long long finalBalance;
		time_t time;
		
	public:
        Operation(unsigned long long finalBalance);
		unsigned long long getUnits();
        bool operator==(const Operation& op) const {return this->time == op.time;}
        bool operator< (const Operation& op) const {return this->time < op.time;}
        friend std::ostream& operator<< (std::ostream& os, const Operation& op);

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
		~Wallet();
        Wallet();
		Wallet(int n);
		Wallet(const char* str);
		// copy constructor explicitly forbidden
		Wallet(const Wallet& wallet) = delete;
        // copy assignment explicitly forbidden
		Wallet& operator= (const Wallet& wallet) = delete;
		// move assignment allowed
		Wallet& operator= (Wallet&& wallet);
		Wallet(Wallet&& wallet);

		Wallet(Wallet&& w1, Wallet&& w2);
		static Wallet fromBinary(const char* str);

		friend Wallet operator* (Wallet& wallet, unsigned long long n);
		friend Wallet operator* (Wallet&& wallet, unsigned long long n);
		friend Wallet operator* (unsigned long long n, Wallet& wallet);
		friend Wallet operator* (unsigned long long n, Wallet&& wallet);
		
		friend Wallet operator+ (Wallet&& wallet, Wallet& wallet2);
		friend Wallet operator+ (Wallet&& wallet, Wallet&& wallet2);
		
		friend Wallet operator- (Wallet&& wallet, Wallet& wallet2);
		friend Wallet operator- (Wallet&& wallet, Wallet&& wallet2);
		
		Wallet& operator+= (Wallet& wallet);
		Wallet& operator+= (Wallet&& wallet);
		Wallet& operator+= (unsigned long long n);

		Wallet& operator-= (Wallet& wallet);
		Wallet& operator-= (Wallet&& wallet);
		Wallet& operator-= (unsigned long long n);
		
		Wallet& operator*= (int n);

		friend bool operator== (const Wallet& wallet, const Wallet& wallet2); 
		friend bool operator< (const Wallet& wallet, const Wallet& wallet2);
		friend bool operator<= (const Wallet& wallet, const Wallet& wallet2);
		friend bool operator> (const Wallet& wallet, const Wallet& wallet2);
		friend bool operator>= (const Wallet& wallet, const Wallet& wallet2);
		friend bool operator!= (const Wallet& wallet, const Wallet& wallet2);

		Operation operator[] (int i) const;
		
		unsigned long long getUnits() const;
		size_t opSize() const;
		
		friend std::ostream& operator<< (std::ostream& os, const Wallet& op);
		 
		// temporary, delete before submitting 
		void printHistory();
};

const Wallet& Empty();

#endif // _WALLET_H_
