/**
* \file gen_array3_main.cpp
*
* Egyszer� tesztprogram a cporta NHF p�ldafeladat bemutat�s�hoz.
*
* Feladat:
*   Fix m�ret� Generikus t�mb megval�s�t�sa.
*
* A mintaprogram lok�lis nyelvi k�rnyezetet is �ll�t.  A magyar �kezetes
* sz�vegek megjelen�t�s�hez
*
* Windows alatt az 1250-es k�dlap-"szabv�ny" szerint kell menteni a f�jlt.
* A helyes megjelen�shez magyar Windows XP alatt az 1250-es k�dlapot kell
* be�ll�tani:
*   regedit:
*     [HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Nls\CodePage]
*        OEMCP=1250
*    Ezen fel�l az output k�perny� fontk�szlet�t Lucida Console t�pus�ra kell
*    �ll�tani.
*
* Linux/UNIX: A modern Linuxok UTF-8-as k�dol�st haszn�lnak alapb�l: ha a
* f�jlt �gy mentj�k, helyesen fognak megjelenni az �kezetek. (P�ld�ul
* LANG=hu_HU.UTF8 be�ll�t�sokkal.)
*
* M�s Unixok eset�ben az   export LANG=hu_HU    paranccsal lehet az adott
* parancs�rtelmez� sz�m�ra megadni a haszn�land� locale-t. Ebben az esetben
* ISO-8859-2 (m�s n�ven latin2) k�dol�ssal kell a f�jlt menteni.
*
* Cporta: A bem�solt f�jlt a b�ng�sz� a megfelel� UTF-8 k�dol�sban fogja
* k�ldeni.
*/
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <locale>
#if defined(WIN32) || defined(_WIN32)
#include <windows.h>
#endif
#include "memtrace.h"
#include "gen_array3.hpp"           // sablon

using namespace std;

/// Saj�t kiv�teloszt�ly a teszthez.
class BajVan {
public:
	/// @param - nem haszn�ljuk semmire
	BajVan(const string&) {}
};

const char msg[] = "\
				   A mintafeladat bemutatja az �kezetes karakterek haszn�lat�t is.\n\
				   Az al�bbi sz�veg windows 1250-es (ISO 8859-2/latin 2) k�dol�s�:\n\
				   �rv�zt�r�t�k�rf�r�g�p �RV�ZT�R�T�K�RF�R�G�P";


/// TESZT 4
/// Adatfile beolvas�s�nak bemutat�s�hoz.
/// Csak dem� nincs funci�ja ebben a feladatban.
void test_4() {
	cout << msg << endl;
	char buf[100];
	fstream os;
	os.exceptions(ifstream::badbit);

	// megnyit�s
	os.open("valami_adat.dat", fstream::in);

	// beolvasas
	while (os.getline(buf, sizeof(buf)))
		cout << buf << endl;
	os.close();
}

/// TESZT 1
void test_1() {
	Array<int> arr;                 // default (50) elem� int t�mb
	int idx;
	int val;
	cout << "default (50) elem� int t�mb" << endl;
	while (cin >> idx >> val) {
		arr[idx] = val;
		cout << "arr[" << idx << "]=" << arr[idx] << endl;
	}
}

/// TESZT 2
void test_2() {
	Array<double, 100> arr;         // 100 elem� double t�mb
	int idx;
	double val;
	cout << "100 elem� double t�mb" << endl;
	while (cin >> idx >> val) {
		arr[idx] = val;
		cout << "arr[" << idx << "]=" << arr[idx] << endl;
	}
}

/// TESZT 3
void test_3() {
	Array<string, 11, BajVan> arr;  // 11 elem� string saj�t kiv�tellel
	int idx;
	string val;
	cout << "11 elem� string sajat kiv�teloszt�llyal" << endl;
	while (cin >> idx >> val) {
		arr[idx] = val;
		cout << "arr[" << idx << "]=" << arr[idx] << endl;
	}
}

/// F�program a standard inputr�l olvas egy eg�sz sz�mot, majd
/// megh�vja az annak megfelel� tesztesetet.
/// A tov�bbi bemenetet �s kimenetet a tesztesetek kezelik.
int main() {
	setlocale(LC_ALL, "");  // a rendszer k�rnyezeti v�ltoz�j�ban megadott nyelvi k�rnyezet be�ll�t�sa
#if defined(WIN32) || defined(_WIN32)
	SetConsoleCP(1250);
	SetConsoleOutputCP(1250);
#endif
	try {
		int nr;
		cin >> nr;        // hanyadik teszteset
		cin.ignore(500, '\n'); // eldobunk max. 500 karaktert a sor v�g�ig
		cout << endl << nr << ". teszteset ind�t�sa:" << endl;
		switch (nr) {
		case 4:
			test_4();   // csak demo, nics funkci�ja a feladatban
			break;

		case 1:
			test_1();   // default (50) elem� int t�mb
			break;

		case 2:
			test_2();   // 100 elem� double t�mb
			break;

		case 3:
			test_3();   // 11 elem� string saj�t kiv�teloszt�llyal
			break;
		default:
			cout << "Nics ilyen teszteset!" << endl;
		}

		// konstans t�mb indexel�s�nek tesztje
		Array<int> ia;
		ia[0] = 12;
		const Array<int> ia2 = ia;
		cout << "Konstans t�mb 0. eleme: " << ia2[0] << endl;

		// kiv�tel elkap�sa
	}
	catch (exception& e) {
		// ki�rjuk, hogy milyen kiv�tel j�tt
		cerr << e.what() << endl;
	}
	catch (BajVan&) {
		cerr << "Saj�t kiv�tel j�tt" << endl;
	}
	catch (...) {
		cerr << "*** Nagy baj van! ****" << endl;
	}

	// itt minden mem�riater�letnek, objektumnak fel kell szabadulnia, hogy a
	// mem�riasziv�rg�s ellen�rizhet� legyen!
	_CrtDumpMemoryLeaks();  // ellen�rzi, hogy volt-e mem�riasziv�rg�s

	return 0;
}