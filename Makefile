wallet.o: wallet.cc
	g++ -Wall -Wextra -O2 -std=c++17 -c wallet.cc

test.o: test.cc
	g++ -Wall -Wextra -O2 -std=c++17 -c test.cc

test:	test.o wallet.o
	g++ -Wall -Wextra -O2 -std=c++17 test.o wallet.o -o test
	
