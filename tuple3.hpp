#ifndef TUPLE3_HPP
#define TUPLE3_HPP

#include <cstddef> ///A NULL miatt kell
#include <stdexcept>
#include <string.h>
#include "memtrace.h"

/// Tuple sablon
/// @param T - adatt�pus
template<class T>
class Tuple3 {
	T *member1;
	T *member2;
	T *member3;
	unsigned int n;
public:
	/// Konstruktorok
	Tuple3();
	Tuple3(T t1);
	Tuple3(T t1, T t2);
	Tuple3(T t1, T t2, T t3);

	/// M�sol� kontruktor
	Tuple3(const Tuple3& t);

	/// Destruktor
	~Tuple3();

	/// Elemsz�m lek�rdez�se
	/// @return elemsz�m
	unsigned int getN() const{ return n; }

	/// Elem lek�rdez�se
	/// @param x - index
	/// @return - referencia az adott index� elemre
	/// @return - hib�s index�rt�k eset�n out_of_range kiv�telt dob
	T& getMember(unsigned int x);

	/// Egyenl�s�g vizsg�lat
	/// @param r_hs - jobb oldali elem referenci�ja
	/// @return - true ha egyenl�ek, false ha nem
	bool operator==(const Tuple3& r_hs) const;

	/// Egyenl�tlens�g vizsg�lat
	/// @param r_hs - jobb oldali elem referenci�ja
	/// @return - true ha nem egyenl�ek, false ha igen
	bool operator!=(const Tuple3& r_hs) const;

	/// �rt�kad� oper�tor
	/// @param r_hs - jobb oldali elem referenci�ja
	/// @return az �tadott �rt�k
	Tuple3<T>& operator=(const Tuple3& r_hs);
};

template<class T>
Tuple3<T>::Tuple3() {
	member1 = NULL;
	member2 = NULL;
	member3 = NULL;
	n = 0;
}

template<class T>
Tuple3<T>::Tuple3(T t1){
	member1 = new T;
	*member1 = t1;
	member2 = NULL;
	member3 = NULL;
	n = 1;
}

template<class T>
Tuple3<T>::Tuple3(T t1, T t2) {
	member1 = new T;
	*member1 = t1;
	member2 = new T;
	*member2 = t2;
	member3 = NULL;
	n = 2;
}

template<class T>
Tuple3<T>::Tuple3(T t1, T t2, T t3) {
	member1 = new T;
	*member1 = t1;
	member2 = new T;
	*member2 = t2;
	member3 = new T;
	*member3 = t3;
	n = 3;
}

template<class T>
T& Tuple3<T>::getMember(unsigned int x) {
	if (x > n || x == 0)
	{
		throw std::out_of_range("Invalid index");
	}
	switch (x)
	{
	case 1:
		return *member1;
		break;
	case 2:
		return *member2;
		break;
	case 3:
		return *member3;
		break;
	default: //ide elvileg soha nem fog eljutni, csaka biztons�g kedv��rt van itt
		throw std::out_of_range("Invalid index");
		break;
	}
}

template<class T>
Tuple3<T>::~Tuple3(){
	if (member1 != NULL)
	{
		delete member1;
	}
	if (member2 != NULL)
	{
		delete member2;
	}
	if (member3 != NULL)
	{
		delete member3;
	}
}

template<class T>
bool Tuple3<T>::operator==(const Tuple3<T>& r_hs) const {
	if (n != r_hs.n)
	{
		return false;
	}
	if (member1 != NULL && *member1 != *r_hs.member1)
	{
		return false;
	}
	if (member2 != NULL && *member2 != *r_hs.member2)
	{
		return false;
	}
	if (member3 != NULL && *member3 != *r_hs.member3)
	{
		return false;
	}
	return true;
}

template<class T>
bool Tuple3<T>::operator!=(const Tuple3<T>& r_hs) const{ //visszavezetj�k a == oper�torra
	if (*this == r_hs)
	{
		return false;
	}
	else
	{
		return true;
	}
}

template<class T>
Tuple3<T>::Tuple3(const Tuple3<T>& t){
	switch (t.n)
	{
	case 0:
		member1 = NULL;
		member2 = NULL;
		member3 = NULL;
		n = 0;
		break;
	case 1:
		member1 = new T;
		*member1 = *t.member1;
		member2 = NULL;
		member3 = NULL;
		n = 1;
		break;
	case 2:
		member1 = new T;
		*member1 = *t.member1;
		member2 = new T;
		*member2 = *t.member2;
		member3 = NULL;
		n = 2;
		break;
	case 3:
		member1 = new T;
		*member1 = *t.member1;
		member2 = new T;
		*member2 = *t.member2;
		member3 = new T;
		*member3 = *t.member3;
		n = 3;
		break;
	default:
		break;
	}
}

template<class T>
Tuple3<T>& Tuple3<T>::operator=(const Tuple3& r_hs){
	//T�r�lj�k a m�r nem sz�ks�ges adatokat, hogy ne legyen mem�ria sziv�rg�s
	if (this->member1 != NULL)delete this->member1;
	if (this->member2 != NULL)delete this->member2;
	if (this->member3 != NULL)delete this->member3;
	switch (r_hs.n)
	{
	case 0:
		this->member1 = NULL;
		this->member2 = NULL;
		this->member3 = NULL;
		this->n = 0;
		break;
	case 1:
		this->member1 = new T;
		*(this->member1) = *r_hs.member1;
		this->member2 = NULL;
		this->member3 = NULL;
		this->n = 1;
		break;
	case 2:
		this->member1 = new T;
		*this->member1 = *r_hs.member1;
		this->member2 = new T;
		*this->member2 = *r_hs.member2;
		this->member3 = NULL;
		this->n = 2;
		break;
	case 3:
		this->member1 = new T;
		*(this->member1) = *r_hs.member1;
		this->member2 = new T;
		*(this->member2) = *r_hs.member2;
		this->member3 = new T;
		*(this->member3) = *r_hs.member3;
		this->n = 3;
		break;
	default:
		break;
	}
	return *this;
}

#endif
