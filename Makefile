wallet.o: wallet.cc wallet.h
	g++ -Wall -Wextra -O2 -std=c++17 -c wallet.cc

test.o: test.cc
	g++ -Wall -Wextra -O2 -std=c++17 -c test.cc

test:	test.o wallet.o
	g++ -Wall -Wextra -O2 -std=c++17 test.o wallet.o -o test

wallet_example.o: wallet_example.cc
	g++ -Wall -Wextra -O2 -std=c++17 -c wallet_example.cc

example: wallet_example.o wallet.o
	g++ -Wall -Wextra -O2 -std=c++17 wallet_example.o wallet.o -o example
	
