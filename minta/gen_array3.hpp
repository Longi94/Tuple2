/**
* \file gen_array3.hpp
*
* Generikus tömb NHF példa feladatának bemutatásához.
* Kész (végleges) feladat.
*
* Feladat:
*   Fix méretû Generikus tömb megvalósítása.
*/

#include <sstream>          /// csak a hibajelzés miatt kell

/// Generikus tömb osztály statikus mérettel
/// @param T - adattípus
/// @param s - méret, default: 50
/// @param E - hibaosztály (indexelési hiba esetén hívódik) defalul: std::range_error
template <class T, int s = 50, typename E = std::out_of_range>
class Array {               // osztálysablon
	T t[s];                 /// adattag, template paraméter a mérete
public:
	/// Indexelés.
	/// @param i - index
	/// @return - referencia az adott indexû elemre
	/// @return - hibás indexérték esetén E() kivételt dob
	T& operator[](int i);

	/// Indexelés konstans függvénye.
	/// @param i - index
	/// @return - referencia az adott indexû elemre
	/// @return - hibás indexérték esetén E() kivételt dob 
	const T& operator[](int i) const;
};

/// index operátor megvalósítása
template <class T, int s, typename E>
T& Array<T, s, E>::operator [](int i) {
	if (i < 0 || i >= s) {
		// megpróbálunk összerakni egy értelmes hibajelzést
		// persze ez így nagyon fapados és ronda
		std::stringstream err;
		err << " **Indexhiba** idx: " << i << " [0," << s - 1 << "]";
		throw E(err.str()); // template paraméterként kapott osztály egy példányát dobjuk
	}
	return t[i];    // megfelelõ elem referenciájával térünk vissza
}

/// konstans példány index operátor megvalósítása
template <class T, int s, typename E>
const T& Array<T, s, E>::operator [](int i) const {
	if (i < 0 || i >= s) {
		// megpróbálunk összerakni egy értelmes hibajelzést
		// persze ez így nagyon fapados és ronda
		std::stringstream err;
		err << " **Indexhiba** idx: " << i << " [0," << s - 1 << "]";
		throw E(err.str()); // template paraméterként kapott osztály egy példányát dobjuk
	}
	return t[i];    // megfelelõ elem referenciájával térünk vissza
}