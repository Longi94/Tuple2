#ifndef STRING_H
#define STRING_H
/**
 * \file string2.h
 * String osztály deklarációja.
 * (latin2 kodolasu fajl)
 *
 */

#include <iostream>   // az ostream miatt kell
#include "memtrace.h"

/**
 * String osztály.
 * A 'pData'-ban vannak a karakterek (a lezáró nullával együtt), 'len' a hossza.
 * A hosszba nem számít bele a lezáró nulla.
 */
class String {
    char *pData;         // pointer az adatra
    unsigned int len;    // hossz lezáró nulla nélkül
public:
  // Konstruktorok és a Destruktor

    /// Konstruktor: egy karakterbõl (createStringFromChar-ból keletkezett)
    /// @param ch - karakter, amibõl a String-et létrehozzuk
    String(char ch);

    /// Default konstruktor is
    /// Konstruktor: egy egy nullával lezárt char sorozatból (createStringFromCharStr)
    /// @param p - pointer a C stringre
    String(const char* p = "");


    /// C stringet ad vissza
    /// @return nullával lezárt karaktersorozatra mutató pointer
    const char* c_str() const {
        return pData;
    }

    /// Másoló konstruktor, ami a createStringFromString-bõl keletkezett
    /// @param s1 - String, amibõl létrehozzuk az új String-et
    String(const String& s1);

    /// Destruktor (disposeString)
    ~String();

  // Egyéb tagfüggvények:
    /// Kiírunk egy Stringet (debug célokra) (ez kész)
    /// Elötte kiírunk egy tetszõleges szöveget.
    /// @param txt - nullával lezárt szövegre mutató pointer
    void printDbg(const char *txt = "") const {
        std::cout << txt << "[" << len << "], "
                  << (pData ? pData : "(NULL)") << std::endl;
    }

  // Operátorok:
    /// Értékadó operátor is kell !
    /// @param rhs_s - jobboldali String
    /// @return baoldali (módosított) string (referenciája)
    String& operator=(const String& rhs_s);

    /// Két Stringet összefûz (concatString)
    /// @param rhs_s - jobboldali String
    /// @return új String, ami tartalmazza a két stringet egmás után
    String operator+(const String& rhs_s) const ;

    /// A string egy megadott indexû elemének REFERENCIÁJÁVAL tér vissza.
    /// charAtString-bõl keletkezett, de ezt bal oldalon is lehet használni
    /// @param idx - charakter indexe
    /// @return karakter (referencia)
    ///         Indexelési hiba esetén const char* kivételt dob (assert helyett).
    char& operator[](unsigned int idx);

    /// A string egy megadott indexû elemének REFERENCIÁJÁVAL tér vissza.
    /// charAtString-bõl keletkezett. Konstans stringre alkalmazható.
    /// Indexelési hiba esetén const char* kivételt dob (assert helyett).
    /// @param idx - charakter indexe
    /// @return karakter (referencia)
    ///         Indexelési hiba esetén const char* kivételt dob (assert helyett).
    const char& operator[](unsigned int idx) const;

  // Barát függvények:
    /// kiír az ostream-re (printString)
    /// @param os - ostream típusú objektum
    /// @param s0 - String, amit kiírunk
    /// @return os
    friend std::ostream& operator<<(std::ostream& os, const String& s0);

    /// Beolvas az istream-rõl egy szót egy string-be.
    /// @param is - istream típusú objektum
    /// @param s0 - String, amibe beolvas
    /// @return is
    friend std::istream& operator>>(std::istream& is, String& s0);
};
#endif

