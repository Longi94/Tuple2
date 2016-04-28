#ifndef STRING_H
#define STRING_H
/**
 * \file string2.h
 * String oszt�ly deklar�ci�ja.
 * (latin2 kodolasu fajl)
 *
 */

#include <iostream>   // az ostream miatt kell
#include "memtrace.h"

/**
 * String oszt�ly.
 * A 'pData'-ban vannak a karakterek (a lez�r� null�val egy�tt), 'len' a hossza.
 * A hosszba nem sz�m�t bele a lez�r� nulla.
 */
class String {
    char *pData;         // pointer az adatra
    unsigned int len;    // hossz lez�r� nulla n�lk�l
public:
  // Konstruktorok �s a Destruktor

    /// Konstruktor: egy karakterb�l (createStringFromChar-b�l keletkezett)
    /// @param ch - karakter, amib�l a String-et l�trehozzuk
    String(char ch);

    /// Default konstruktor is
    /// Konstruktor: egy egy null�val lez�rt char sorozatb�l (createStringFromCharStr)
    /// @param p - pointer a C stringre
    String(const char* p = "");


    /// C stringet ad vissza
    /// @return null�val lez�rt karaktersorozatra mutat� pointer
    const char* c_str() const {
        return pData;
    }

    /// M�sol� konstruktor, ami a createStringFromString-b�l keletkezett
    /// @param s1 - String, amib�l l�trehozzuk az �j String-et
    String(const String& s1);

    /// Destruktor (disposeString)
    ~String();

  // Egy�b tagf�ggv�nyek:
    /// Ki�runk egy Stringet (debug c�lokra) (ez k�sz)
    /// El�tte ki�runk egy tetsz�leges sz�veget.
    /// @param txt - null�val lez�rt sz�vegre mutat� pointer
    void printDbg(const char *txt = "") const {
        std::cout << txt << "[" << len << "], "
                  << (pData ? pData : "(NULL)") << std::endl;
    }

  // Oper�torok:
    /// �rt�kad� oper�tor is kell !
    /// @param rhs_s - jobboldali String
    /// @return baoldali (m�dos�tott) string (referenci�ja)
    String& operator=(const String& rhs_s);

    /// K�t Stringet �sszef�z (concatString)
    /// @param rhs_s - jobboldali String
    /// @return �j String, ami tartalmazza a k�t stringet egm�s ut�n
    String operator+(const String& rhs_s) const ;

    /// A string egy megadott index� elem�nek REFERENCI�J�VAL t�r vissza.
    /// charAtString-b�l keletkezett, de ezt bal oldalon is lehet haszn�lni
    /// @param idx - charakter indexe
    /// @return karakter (referencia)
    ///         Indexel�si hiba eset�n const char* kiv�telt dob (assert helyett).
    char& operator[](unsigned int idx);

    /// A string egy megadott index� elem�nek REFERENCI�J�VAL t�r vissza.
    /// charAtString-b�l keletkezett. Konstans stringre alkalmazhat�.
    /// Indexel�si hiba eset�n const char* kiv�telt dob (assert helyett).
    /// @param idx - charakter indexe
    /// @return karakter (referencia)
    ///         Indexel�si hiba eset�n const char* kiv�telt dob (assert helyett).
    const char& operator[](unsigned int idx) const;

  // Bar�t f�ggv�nyek:
    /// ki�r az ostream-re (printString)
    /// @param os - ostream t�pus� objektum
    /// @param s0 - String, amit ki�runk
    /// @return os
    friend std::ostream& operator<<(std::ostream& os, const String& s0);

    /// Beolvas az istream-r�l egy sz�t egy string-be.
    /// @param is - istream t�pus� objektum
    /// @param s0 - String, amibe beolvas
    /// @return is
    friend std::istream& operator>>(std::istream& is, String& s0);
};
#endif

