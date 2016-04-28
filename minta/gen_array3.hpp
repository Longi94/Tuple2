/**
* \file gen_array3.hpp
*
* Generikus t�mb NHF p�lda feladat�nak bemutat�s�hoz.
* K�sz (v�gleges) feladat.
*
* Feladat:
*   Fix m�ret� Generikus t�mb megval�s�t�sa.
*/

#include <sstream>          /// csak a hibajelz�s miatt kell

/// Generikus t�mb oszt�ly statikus m�rettel
/// @param T - adatt�pus
/// @param s - m�ret, default: 50
/// @param E - hibaoszt�ly (indexel�si hiba eset�n h�v�dik) defalul: std::range_error
template <class T, int s = 50, typename E = std::out_of_range>
class Array {               // oszt�lysablon
	T t[s];                 /// adattag, template param�ter a m�rete
public:
	/// Indexel�s.
	/// @param i - index
	/// @return - referencia az adott index� elemre
	/// @return - hib�s index�rt�k eset�n E() kiv�telt dob
	T& operator[](int i);

	/// Indexel�s konstans f�ggv�nye.
	/// @param i - index
	/// @return - referencia az adott index� elemre
	/// @return - hib�s index�rt�k eset�n E() kiv�telt dob 
	const T& operator[](int i) const;
};

/// index oper�tor megval�s�t�sa
template <class T, int s, typename E>
T& Array<T, s, E>::operator [](int i) {
	if (i < 0 || i >= s) {
		// megpr�b�lunk �sszerakni egy �rtelmes hibajelz�st
		// persze ez �gy nagyon fapados �s ronda
		std::stringstream err;
		err << " **Indexhiba** idx: " << i << " [0," << s - 1 << "]";
		throw E(err.str()); // template param�terk�nt kapott oszt�ly egy p�ld�ny�t dobjuk
	}
	return t[i];    // megfelel� elem referenci�j�val t�r�nk vissza
}

/// konstans p�ld�ny index oper�tor megval�s�t�sa
template <class T, int s, typename E>
const T& Array<T, s, E>::operator [](int i) const {
	if (i < 0 || i >= s) {
		// megpr�b�lunk �sszerakni egy �rtelmes hibajelz�st
		// persze ez �gy nagyon fapados �s ronda
		std::stringstream err;
		err << " **Indexhiba** idx: " << i << " [0," << s - 1 << "]";
		throw E(err.str()); // template param�terk�nt kapott oszt�ly egy p�ld�ny�t dobjuk
	}
	return t[i];    // megfelel� elem referenci�j�val t�r�nk vissza
}