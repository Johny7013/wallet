// program to testowania, czy rzeczy dzialaja

#include <bits/stdc++.h>
#include "wallet.h"
using namespace std;

static const uint UNITS_IN_B = 100000000;

using std::move;

int main() {

    //Wallet wer((double)3);
    //cout << "Po pierwszej operacji w w0 portfelu bylo " << wer[0].getUnits() << " B" <<  endl;

    Wallet er("123");
    Wallet ert(0);
    cout << "Po pierwszej operacji w w0 portfelu bylo " << ert[0].getUnits() << " B" <<  endl;


	Wallet w0;
	cout << "Po pierwszej operacji w w0 portfelu bylo " << w0[0].getUnits() << " B" <<  endl;
	Wallet w(4);
	cout << "Po pierwszej operacji w w(4) portfelu bylo " << w[0].getUnits() << " B" <<  endl;

	// check if copy constuctor successfully forbidden
	//Wallet w1 = w0;
    // check if copy assignment successfully forbidden
	//w0 = w;

	// check move constuctor
    Wallet w2 = std::move(Wallet(42));
    cout << "Po pierwszej operacji w w2 portfelu bylo " << w2[0].getUnits() << " B" <<  endl;

    // check excpetion tooManyB
    //Wallet w3(22000000);

    // check Wallet(str)
    Wallet w4("34,67");
    cout << "Po pierwszej operacji w w4 portfelu bylo " << w4[0].getUnits() << " B" <<  endl;

    // check invalid_argument exception
    //Wallet w5("as,78");

    // check leading zeroes
    Wallet w6("  000,78657      ");
    cout << "Po pierwszej operacji w w6 portfelu bylo " << w6[0].getUnits() << " B" <<  endl;

    w6 += 2;
    w4 += 3;
    w6 += 1;

    // check Wallet( Wallet&& w1, Wallet&& w2)
    Wallet w7(std::move(w4), std::move(w6));
    for(int i = 0; i < 6; i++){
        cout << "Po " << i << "-tej operacji w w7 portfelu bylo " << w7[i].getUnits() << " B" <<  endl;
    }

    // check Wallet::fromBinary(str)
    Wallet ww8 = Wallet::fromBinary("100000");
    cout << "Po pierwszej operacji w w8 portfelu bylo " << ww8[0].getUnits() << " B" <<  endl;
    Wallet ww6 = Wallet::fromBinary("1010");
    cout << "Po pierwszej operacji w w8 portfelu bylo " << ww8[0].getUnits() << " B" <<  endl;

    // check Operation to date
    cout << ww8[0] <<  endl;

    
    // check move assignment 
	Wallet ww7(7);
	ww7 = Wallet(10);

	
	cout << "Po drugiej operacji w w7 portfelu bylo " << ww7[1].getUnits() << " B" << endl;
	
	// check operation out of bounds exception
	//cout << "Po trzeciej operacji w w7 portfelu bylo " << w7[2].getUnits() << " B" << endl;
	
	Wallet w8(8), w9(9);
	w8 += w9;
	
	w8 *= 3;
	
	w8 -= Wallet(5);
	
	w8 += Wallet(5);
	
	w8 += 3;
	w8 -= 3;

	
	Wallet w10(51);
	
	cout << (w10 == w8) << endl;
	cout << (Wallet(51) <= Wallet(50)) << endl;
	
	Wallet vw1(1), vw2(2);
	Wallet vw3 = vw1 * 42;
	Wallet vw4 = 42 * vw2;
	Wallet vw5 = Wallet(1) * 42;
	Wallet vw6 = 42 * Wallet(2);
	//Wallet vw7 = Wallet(3) *= 42;

    //vw7.printHistory();
	
	
	
    Wallet ww1(1), ww2(2);
    //Wallet suma1 = ww1 + Wallet(1); // błąd kompilacji
    Wallet suma2 = Wallet(2) + ww2; // OK, w ww2 jest 0 B po operacji
                                   // i jeden nowy wpis w historii,
                                   // a w suma2 jest w2.getUnits() + 2 B.
                                   // Historia operacji powstałego obiektu
                                   // zależy od implementacji.
    //Wallet suma3 = ww1 + suma2;  // błąd kompilacji
    Wallet suma4 = Wallet(1) + Wallet(2);  // OK, suma4 ma dwa wpisy
                                           // w historii i 3 B

    //ww2.printHistory();  
    
    Wallet a = Wallet(8);
    cout << a << endl;
    
    Wallet c = 15000000;
    std::cout << (c == Wallet(5000000)) << std::endl;
    Wallet d = 3000000;
    
    c.~Wallet();
    d.~Wallet();
    
    //3 += Wallet(1); //CE
    
        Wallet q1, q2;
    q1 = Wallet(1); // OK
    //q1 = q2; // błąd kompilacji


	/////////////////////////////////////////////////// TESTY Z FB
    Wallet r1(1), r2(2);
    //r1 + r2; // błąd kompilacji
    //Wallet xsuma1 = r1 + Wallet(1); // błąd kompilacji
    Wallet xsuma2 = Wallet(2) + r2; // OK
    assert(r2.getUnits() == 0);
    assert(r2.opSize() == 2);
    assert(xsuma2.getUnits() == 4 * UNITS_IN_B);
    //Wallet xsuma3 = xsuma1 + xsuma2;  // błąd kompilacji
    Wallet xsuma4 = Wallet(1) + Wallet(2);  // OK
    assert(xsuma4.opSize() == 2);
    assert(xsuma4.getUnits() == 3 * UNITS_IN_B);

    Wallet s1, s2;
    bool b;
    float f;
    //Wallet s3(true); // błąd kompilacji
    //Wallet s4('a');  // błąd kompilacji
    //Wallet s5(f); // błąd kompilacji
    //s1 += "10"; // błąd kompilacji
    //s1 = s2 + "10"; // błąd kompilacji
    //b = "10" < s2; // błąd kompilacji

    s1 += Wallet(3);
    s1 *= 3;
    b = 2 < s2;
    Wallet suma5 = 2 + s2;
    Wallet suma6 = Wallet(1) + 2;
    //Wallet suma7 = 2.5 + s2; // błąd kompilacji
    //Wallet suma8 = Wallet(1) - Wallet(2); // exception

    Wallet t1(10000000), t2(10000000);
    //Wallet t3(2000000); // exception
    t1.~Wallet();
    t2.~Wallet();

    Wallet u1(1), u2(2);
    u1 += 1;
    u2 += Wallet(1);
    u1 += 0;
    //u2 += 1 += Wallet(1); // CE
    Wallet u3(std::move(u1), std::move(u2));
    //assert(u3.opSize() == 7);
    //assert(u3.getUnits() == 7 * UNITS_IN_B);

    Wallet x1(1), x2(2);
    assert(x1 < x2);
    assert(x1 <= x2);
    assert(x1 <= x1);
    assert(x1 != x2);
    assert(x2 >= x1);
    assert(x2 >= x2);
    assert(x2 > x1);

    assert(Wallet(1) < x2);
    assert(Wallet(1) <= x2);
    assert(Wallet(1) <= Wallet(1));
    assert(Wallet(1) != x2);
    assert(x2 >= Wallet(1));
    assert(x2 >= x2);
    assert(x2 > Wallet(1));

    assert(Wallet(1) < Wallet(2));
    assert(Wallet(1) <= Wallet(2));
    assert(Wallet(1) <= Wallet(1));
    assert(Wallet(1) != Wallet(2));
    assert(Wallet(2) >= Wallet(1));
    assert(Wallet(2) >= Wallet(2));
    assert(Wallet(2) > Wallet(1));

	Wallet(1) += 2;
    //Wallet lolz = Wallet(1) += 2; // CE
    //Wallet omg = Wallet(3) += Wallet(2); // CE
    //std::cout << lolz << "\n";
    //std::cout << lolz[0] << "\n";

    //Wallet emp = Empty();
    assert(Empty() == 0);
    assert(Empty() < Wallet(1));
    assert(Empty().getUnits() == 0);
    assert(Empty().opSize() == 1);
    assert(Empty()[0].getUnits() == 0);
    //Empty() += Wallet(1); // błąd kompilacji

    Wallet xw1; 
    assert(xw1 == Empty());
    assert(xw1.opSize() == 1);

    Wallet xw2(1), xw3(1);
    assert(xw2.opSize() == 1);
    assert(xw2.getUnits() == UNITS_IN_B);
    assert(xw2 == 1);
    assert(1 == xw2);
    assert(xw2 == xw3);

    assert(Wallet::fromBinary("100") == Wallet(4));
    std::string str(" 1.2000 ");
    assert(Wallet(" 1.2000 ") == Wallet("1,2"));
    assert(Wallet(str) == Wallet("1,2"));
     //Wallet("1.a"); // exception

    assert(Wallet(2) + xw2 == Wallet(3));
    assert(Wallet(1) + Wallet(2) == Wallet(3));
    assert(1 + 2 == Wallet(3));

    Wallet xw4;
    assert(xw4.opSize() == 1);
	
    xw4 += 2;
    assert(xw4.opSize() == 2);
   
    assert(xw4[0] <= xw4[1]);
     std::cout << "ok" << std::endl;
    assert(xw4[1].getUnits() == xw4.getUnits());
		
    xw4 *= 3;
    assert(xw4.opSize() == 3);
    assert(xw4[2].getUnits() == 6 * UNITS_IN_B);

    assert(Wallet(move(xw4)).opSize() == 4);

    Wallet xw5{2};
    //Wallet w6{true}; // błąd kompilacji
    Wallet xw7 = Wallet(10) - xw5;
    assert(xw5 == Wallet(4));
    assert(xw7 == Wallet(8));
    
    Wallet fw1, fw2;
    bool fb;
    float ff;
    
    fw1 += Wallet(3);
    fw1 *= 3;
    fb = 2 < fw2;
    Wallet fsuma2 = 2 + fw2;
    
    //Wallet fw3(true);
    //Wallet fw4('a');
    //Wallet fw5(ff);
    //fw1 += "10.0";
    //Wallet lel("123");
    //fw1 = Wallet(1) + "10.0";
    //fb = fw2 < "10.0" ;
    //Wallet h(1.23);
	//Wallet xx = "10.0" + Wallet(1);
	
	Wallet sum = 1 + Wallet(10);
	std::cout << sum.opSize() << std::endl;
	std::cout << Wallet(Wallet(1)).opSize() << std::endl;
	
	Wallet t(3);
	//t[0] = std::move(s[0]);
	
	t += Wallet(1);
	cout << t[1] << endl;
	
	//Empty() += Wallet(1);
	
	Wallet g = Wallet(1);
	g *= 2;
	
	return 0;
}


