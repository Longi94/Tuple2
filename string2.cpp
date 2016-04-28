/**
 *
 * \file string2.cpp
 * String oszt�ly megval�s�t�sa.
 * (iso-8859-2 k�dol�s� fajl)
 *
 */
#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS 1
#endif

#include <iostream>             // Ki�rat�shoz
#include <cstring>              // Stringm�veletekhez

// malloc, new fel�ldefini�l�s�val k�sz�tett mem�riasziv�rg�s �s konzisztencia ellen�rz�
#include "memtrace.h"           // a standard headerek ut�n kell lennie
#include "string2.h"

using namespace std;

/// Konstruktor: egy char karakterb�l (createStrFromChar)
String::String(char ch) {
   // Meghat�rozzuk a hossz�t
    len = 1;
    // Lefoglalunk a helyet a hossznak + a lezar� null�nak
    pData = new char[len+1];
    // Betessz�k a karaktert
    pData[0] = ch;
    pData[1] = '\0';
}

// Destruktor (disposeString)
String::~String() { delete[] pData; }

// Konstruktor: egy null�val lez�rt char sorozatb�l (createStringFromCharStr)
String::String(const char *p) {
    // Meghat�rozzuk a hossz�t
    len = strlen(p);
    // Helyet foglalunk
    pData = new char[len+1];
    // Bem�soljuk a stringet, ami le van z�rva 0-val �gy haszn�lhat� az strcpy is
    strcpy(pData, p);
}

// M�sol� konstruktor
String::String(const String& s1) {
    // Meghat�rozzuk a hossz�t
    len = s1.len;
    // Helyet foglalunk
    pData = new char[len+1];
    // Bem�soljuk a stringet, ami le van z�rva 0-val �gy haszn�lhat� az strcpy is
    strcpy(pData, s1.pData);
}

// operator=
String& String::operator=(const String& rhs_s) {
    if (this != &rhs_s) {
        delete[] pData;
        len = rhs_s.len;
        // Helyet foglalunk
        pData = new char[len+1];
        // Bem�soljuk a stringet, ami le van z�rva 0-val �gy haszn�lhat� az strcpy is
        strcpy(pData, rhs_s.pData);
    }
    return *this;
}

// [] oper�torok: egy megadott index� elem REFERENCI�J�VAL t�rnek vissza.
// indexhiba eset�n dobjon egy const char * t�pus� hib�t!
char& String::operator[](unsigned int idx) {
    if (idx >= len) throw "String: indexelesi hiba";
    return pData[idx];
}

const char& String::operator[](unsigned int idx) const {
    if (idx >= len) throw "String: indexelesi hiba";
    return pData[idx];
}

// + oper�tor, ami k�t stringet ad �ssze (concatString)
String String::operator+(const String& rhs_s) const {
    String temp;		// ide ker�l az eredm�ny
    // Meghat�rozza az �j string hossz�t
    temp.len = len + rhs_s.len;
    // Felszabad�tja a temp adattaer�let�t
    delete []temp.pData;
    // lefoglalja a mem�ri�t az �j stringnek.
    temp.pData = new char[temp.len+1];
    // Az elej�re bem�solja az els� stringet
    strcpy(temp.pData, pData);
    // Bem�solja a m�sodik stringet.
    strcat(temp.pData, rhs_s.pData);

    return temp;		// visszat�r az eredm�nnyel

}

// << operator, ami ki�r az ostream-re
std::ostream& operator<<(std::ostream& os, const String& s0) {
    os << s0.pData;
    return os;
}

// << oper�tor, ami beolvas az istreamr�l egy sz�t
std::istream& operator>>(std::istream& is, String& s0) {
    unsigned char ch;
    s0 = String("");            // �res string, ehhez f�z�nk hozz�
	std::ios_base::fmtflags fl = is.flags(); // eltessz�k a r�gi flag-eket
	is.setf(ios_base::skipws);			// az elej�n eldobjuk a ws-t
    while (is >> ch) {
	    is.unsetf(ios_base::skipws);	// ut�na pedig m�r nem
        if (isspace(ch)) {
            is.putback(ch);             // na ezt nem k�rj�k
            break;
        } else {
            s0 = s0 + ch;               // v�g�re f�zz�k a karaktert
        }
    }
	is.setf(fl);						// vissza�ll�tjuk a flag-eket
    return is;
}
