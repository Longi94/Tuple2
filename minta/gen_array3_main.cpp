/**
* \file gen_array3_main.cpp
*
* Egyszerû tesztprogram a cporta NHF példafeladat bemutatásához.
*
* Feladat:
*   Fix méretû Generikus tömb megvalósítása.
*
* A mintaprogram lokális nyelvi környezetet is állít.  A magyar ékezetes
* szövegek megjelenítéséhez
*
* Windows alatt az 1250-es kódlap-"szabvány" szerint kell menteni a fájlt.
* A helyes megjelenéshez magyar Windows XP alatt az 1250-es kódlapot kell
* beállítani:
*   regedit:
*     [HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Nls\CodePage]
*        OEMCP=1250
*    Ezen felül az output képernyõ fontkészletét Lucida Console típusúra kell
*    állítani.
*
* Linux/UNIX: A modern Linuxok UTF-8-as kódolást használnak alapból: ha a
* fájlt így mentjük, helyesen fognak megjelenni az ékezetek. (Például
* LANG=hu_HU.UTF8 beállításokkal.)
*
* Más Unixok esetében az   export LANG=hu_HU    paranccsal lehet az adott
* parancsértelmezõ számára megadni a használandó locale-t. Ebben az esetben
* ISO-8859-2 (más néven latin2) kódolással kell a fájlt menteni.
*
* Cporta: A bemásolt fájlt a böngészõ a megfelelõ UTF-8 kódolásban fogja
* küldeni.
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

/// Saját kivételosztály a teszthez.
class BajVan {
public:
	/// @param - nem használjuk semmire
	BajVan(const string&) {}
};

const char msg[] = "\
				   A mintafeladat bemutatja az ékezetes karakterek használatát is.\n\
				   Az alábbi szöveg windows 1250-es (ISO 8859-2/latin 2) kódolású:\n\
				   árvíztûrõtükörfúrógép ÁRVÍZTÛRÕTÜKÖRFÚRÓGÉP";


/// TESZT 4
/// Adatfile beolvasásának bemutatásához.
/// Csak demó nincs funciója ebben a feladatban.
void test_4() {
	cout << msg << endl;
	char buf[100];
	fstream os;
	os.exceptions(ifstream::badbit);

	// megnyitás
	os.open("valami_adat.dat", fstream::in);

	// beolvasas
	while (os.getline(buf, sizeof(buf)))
		cout << buf << endl;
	os.close();
}

/// TESZT 1
void test_1() {
	Array<int> arr;                 // default (50) elemû int tömb
	int idx;
	int val;
	cout << "default (50) elemû int tömb" << endl;
	while (cin >> idx >> val) {
		arr[idx] = val;
		cout << "arr[" << idx << "]=" << arr[idx] << endl;
	}
}

/// TESZT 2
void test_2() {
	Array<double, 100> arr;         // 100 elemû double tömb
	int idx;
	double val;
	cout << "100 elemû double tömb" << endl;
	while (cin >> idx >> val) {
		arr[idx] = val;
		cout << "arr[" << idx << "]=" << arr[idx] << endl;
	}
}

/// TESZT 3
void test_3() {
	Array<string, 11, BajVan> arr;  // 11 elemû string saját kivétellel
	int idx;
	string val;
	cout << "11 elemû string sajat kivételosztállyal" << endl;
	while (cin >> idx >> val) {
		arr[idx] = val;
		cout << "arr[" << idx << "]=" << arr[idx] << endl;
	}
}

/// Fõprogram a standard inputról olvas egy egész számot, majd
/// meghívja az annak megfelelõ tesztesetet.
/// A további bemenetet és kimenetet a tesztesetek kezelik.
int main() {
	setlocale(LC_ALL, "");  // a rendszer környezeti változójában megadott nyelvi környezet beállítása
#if defined(WIN32) || defined(_WIN32)
	SetConsoleCP(1250);
	SetConsoleOutputCP(1250);
#endif
	try {
		int nr;
		cin >> nr;        // hanyadik teszteset
		cin.ignore(500, '\n'); // eldobunk max. 500 karaktert a sor végéig
		cout << endl << nr << ". teszteset indítása:" << endl;
		switch (nr) {
		case 4:
			test_4();   // csak demo, nics funkciója a feladatban
			break;

		case 1:
			test_1();   // default (50) elemû int tömb
			break;

		case 2:
			test_2();   // 100 elemû double tömb
			break;

		case 3:
			test_3();   // 11 elemû string saját kivételosztállyal
			break;
		default:
			cout << "Nics ilyen teszteset!" << endl;
		}

		// konstans tömb indexelésének tesztje
		Array<int> ia;
		ia[0] = 12;
		const Array<int> ia2 = ia;
		cout << "Konstans tömb 0. eleme: " << ia2[0] << endl;

		// kivétel elkapása
	}
	catch (exception& e) {
		// kiírjuk, hogy milyen kivétel jött
		cerr << e.what() << endl;
	}
	catch (BajVan&) {
		cerr << "Saját kivétel jött" << endl;
	}
	catch (...) {
		cerr << "*** Nagy baj van! ****" << endl;
	}

	// itt minden memóriaterületnek, objektumnak fel kell szabadulnia, hogy a
	// memóriaszivárgás ellenõrizhetõ legyen!
	_CrtDumpMemoryLeaks();  // ellenõrzi, hogy volt-e memóriaszivárgás

	return 0;
}