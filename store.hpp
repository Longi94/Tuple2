#ifndef STORE_HPP
#define STORE_HPP

#include "tuple3.hpp"
#include <iostream>
#include <stdexcept>
#include "memtrace.h"

/// T�r�l� sablon
/// @param T - elemt�pus
template<class T>
class Store{      // oszt�lysablon
	Tuple3<T>* t[100];
	unsigned int n;
public:
	///Konstruktor
	Store(){ n = 0; }

	///Destruktor
	~Store(){ }

	/// T�rol� ki�r�t�se
	void clear();

	/// Elem hozz�ad�sa a t�rol�hoz
	/// @param tuple - Az elem
	/// @return  - overflow_error hib�t dob ha a t�rol� tele van
	void add(const Tuple3<T>& tuple);

	/// A t�rol�ban l�v� �sszes Tuple x-edik elemek halmaz�nak ki�r�sa
	/// @param x - index
	/// @return - hib�s indexel�s eset�n out_of_range hib�t dob
	void getset(unsigned int x) const;

	/// A t�rol�ban l�v� elemek sz�m�nak lek�rdez�se
	/// @return elemsz�m
	unsigned int getN() const { return n; }

	/// Indexel�s oper�tor
	/// @param idx - az index
	/// @return a keresett pointer
	/// @return out_of_range hib�t dob ha rossz az index
	Tuple3<T>* operator[](unsigned int idx) const;
};

template<class T>
void Store<T>::clear(){
	for (size_t i = 0; i < n; i++)
	{
		delete t[i];
		t[i] = NULL;
	}
	n = 0;
}

template<class T>
void Store<T>::add(const Tuple3<T>& tuple){
	if (n == 100)
	{
		throw std::overflow_error("Store is full");
	}
	t[n] = new Tuple3<T>;
	*t[n] = tuple;
	n++;
}

template<class T>
void Store<T>::getset(unsigned int x) const{
	bool first = true, prev = false; //hogy tudjuk, hogy mikor kell vessz�t kirakni
	unsigned int i;
	if (x > 3 || x == 0)
	{
		throw std::out_of_range("Invalid index");
	}
	std::cout << "{";
	for (i = 0; i < n; i++)
	{
		try{
			if (!first && prev)
			{
				std::cout << ",";
			}
			std::cout << t[i]->getMember(x);
			first = false;
			prev = true;
		}
		catch (...){ prev = false; }
	}
	std::cout << "}" << std::endl;
}

template<class T>
Tuple3<T>* Store<T>::operator[](unsigned int idx) const{
	if (idx < 0 || idx > n)
	{
		throw std::out_of_range("Invalid index");
	}
	return t[idx];
}

#endif
