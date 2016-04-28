#include <iostream> /// Standard bemenet, kimenet
#include <fstream> /// f�jlb�l olvas�shoz kell
#include "memtrace.h"
#include "tuple3.hpp"
#include "store.hpp"
#include "string2.h" /// Laboron ek�sz�tett String oszt�ly


using namespace std;

/// BEOLVASAS
void readdat(Store<int>& storeint){
	FILE* input_int;
	int n, i = 0;
	input_int = fopen("input_int.dat", "r");

	if (input_int != NULL){
		// A f�jlb�l olvas�shoz sz�ks�ges v�ltoz�k
		Tuple3<int> temp0;
		Tuple3<int> temp1(0);
		Tuple3<int> temp2(0, 0);
		Tuple3<int> temp3(0, 0, 0);

		// Form�zott f�jlba olvas�s X:{X,X,X} form�ban, ahol a Tuple elemsz�m�t�l f�gg�en t�bb esetre kell bontani.
		// Ezzel egyben a t�rol� add() f�ggv�ny�t is tesztelj�k
		while (fscanf(input_int, "%d:", &n) != EOF && i++ < 100)
		{
			switch (n)
			{
			case 0:
				fscanf(input_int, "{}\n");
				storeint.add(temp0);
				break;
			case 1:
				fscanf(input_int, "{%d}\n", &temp1.getMember(1));
				storeint.add(temp1);
				break;
			case 2:
				fscanf(input_int, "{%d,%d}\n", &temp2.getMember(1), &temp2.getMember(2));
				storeint.add(temp2);
				break;
			case 3:
				fscanf(input_int, "{%d,%d,%d}\n", &temp3.getMember(1), &temp3.getMember(2), &temp3.getMember(3));
				storeint.add(temp3);
				break;
			default:
				break;
			}
		}
		i = i == 101 ? 100 : i;
	}
}

/// TEST_1
/// != oper�tor tesztel�se (ezzel egyben a == oper�tort is tesztelj�k)
void test_1(){
	int n;
	int i = 0;
	bool first = true;
	Tuple3<int> tuple0;
	Tuple3<int> tuple1(0);
	Tuple3<int> tuple2(0, 0);
	Tuple3<int> tuple3(0, 0, 0);
	Tuple3<int> temp0;
	Tuple3<int> temp1;

	//Tuple-k beolvas�sa a standar bemenetr�l
	while (scanf("%d:", &n)){
		switch (n)
		{
		case 0:
			scanf("{}");
			if (first) temp0 = tuple0;
			else temp1 = tuple0;
			break;
		case 1:
			scanf("{%d}", &tuple1.getMember(1));
			if (first) temp0 = tuple1;
			else temp1 = tuple1;
			break;
		case 2:
			scanf("{%d,%d}", &tuple2.getMember(1), &tuple2.getMember(2));
			if (first) temp0 = tuple2;
			else temp1 = tuple2;
			break;
		case 3:
			scanf("{%d,%d,%d}", &tuple3.getMember(1), &tuple3.getMember(2), &tuple3.getMember(3));
			if (first) temp0 = tuple3;
			else temp1 = tuple3;
			break;
		default:
			break;
		}
		if (!first) //Minden m�sodik beolvasott tuple ut�n ki�rja hogy a k�t beolvasott tuple egyenl� vagy, nem egyenl�.
		{
			if (temp0 != temp1)
				cout << "Nem egyenloek" << endl;
			else
				cout << "Egyenloek" << endl;
		}
		first = !first;
		i++;
	}
}

/// TEST_2
/// getN �s getMember tesztel�se
void test_2(Store<int>& storeint){
	// Ki�rjuk a beolvasott tuple-k k�z�l az els� t�z elemsz�m�t.
	cout << "storeint elso 10 tuplejenek elemszama:";
	for (size_t i = 0; i < 10; i++)
	{
		cout << " " << storeint[i]->getN();
	}
	cout << endl;
	//Azt�n ki�rjuk ezeknek az elemeti.
	cout << "storeint elso 10 tupleje:" << endl;
	for (size_t i = 0; i < 10; i++)
	{
		switch (storeint[i]->getN())
		{
		case 0:
			cout << "{}" << endl;
			break;
		case 1:
			cout << "{" << storeint[i]->getMember(1) << "}" << endl;;
			break;
		case 2:
			cout << "{" << storeint[i]->getMember(1) << "," << storeint[i]->getMember(2) << "}" << endl;
			break;
		case 3:
			cout << "{" << storeint[i]->getMember(1) << "," << storeint[i]->getMember(2) << "," << storeint[i]->getMember(3) << "}" << endl;;
			break;
		default:
			break;
		}
	}
}

/// TEST_3
///A halmaz lek�rdez� getset tesztel�se
void test_3(Store<int>& storeint){
	for (size_t i = 1; i < 4; i++)
	{
		cout << i << ". elemek halmaza: ";
		storeint.getset(i);
		cout << endl;
	}
}

/// TEST_4
/// kiv�tel kezel�sek tesztel�se
void test_4(Store<int>& storeint){
	Tuple3<int> tmp(0, 0, 0);
	Tuple3<int>* temp = NULL;
	for (size_t i = 0; i < 5; i++) //getMember indexel�s�nek kiv�tel kezel�se
	{
		try{
			cout << "storeint[0]->getMember(" << i << "): ";
			cout << storeint[0]->getMember(i) << endl;
		}
		catch (exception &e){
			cout << e.what() << endl;
		}
	}
	try{
		cout << "storeint[0]->getMember(2014): ";
		cout << storeint[0]->getMember(2014) << endl;
	}
	catch (exception &e){
		cout << e.what() << endl;
	}
	cout << endl;
	for (size_t i = 0; i < 5; i+=4)
	{
		try{ //getset indexel�s�nek kiv�tel kezel�se
			cout << "storeint.getset(" << i << ") = ";
			storeint.getset(i);
		}
		catch (exception &e){
			cout << e.what() << endl;
		}
	}
	cout << endl;
	try{ //A t�rol� t�lt�lt�s�nek kiv�tel kezel�se
		for (size_t i = storeint.getN(); i < 101; i++)
		{
			storeint.add(tmp);
		}
	}
	catch (exception &e){
		cout << e.what() << endl;
	}
	cout << endl;
	try{ //a t�rol� index oper�tor�nak kiv�tel kezel�se
		cout << "temp = storeint[101]: ";
		temp = storeint[101];
	}
	catch (exception &e){
		cout << e.what() << endl;
	}

}

/// TEST_5
/// Tuple valamennyi funkcionalit�s�nak tesztel�se a String osztlyon
void test_5(){
	// Laboron l�trehozott dinamikus String oszt�llyal l�tre hozott Tuple-k
	Tuple3<String> s0;
	Tuple3<String> s1 = Tuple3<String>("alma");
	Tuple3<String> s2 = Tuple3<String>("Visual", "Studio");
	Tuple3<String> s3 = Tuple3<String>("egy", "ketto", "harom");
	Tuple3<String> s4 = Tuple3<String>("negy", "ot", "hat");

	cout << endl;

	// T�rol� a string t�pus� tuple-knek
	Store<String> storestring;
	// Hozz�adjuk a l�trehozott tuple-ket
	storestring.add(s1);
	storestring.add(s2);
	storestring.add(s3);
	storestring.add(s4);

	// getset tesztel�se
	for (size_t i = 1; i < 4; i++)
	{
		storestring.getset(i);
	}
	///clear tesztel�se
	storestring.clear();
}

/// F�program a standard inputr�l olvas egy eg�sz sz�mot, majd
/// megh�vja az annak megfelel� tesztesetet.
/// A tov�bbi bemenetet �s kimenetet a tesztesetek kezelik.
int main()
{
	int n;

	// T�rol� l�trehoz�sa az int t�pus� Tuple t�rol�s�hoz
	Store<int> storeint;
	readdat(storeint); //beolvas�s

	cin >> n;
	switch (n)
	{
	case 1:
		test_1();
		break;
	case 2:
		test_2(storeint);
		break;
	case 3:
		test_3(storeint);
		break;
	case 4:
		test_4(storeint);
		break;
	case 5:
		test_5();
		break;
	default:
		break;
	}
	storeint.clear();
    return 0;
}
