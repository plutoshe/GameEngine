#pragma once
#include <iostream>
#include "Log.h"
template<class T>
class Vectors
{
public:
	Vectors();
	Vectors(const Vectors<T> &p);
	void operator=(const Vectors<T> &p);

	~Vectors();

	void clear();
	void fixedSize();
	void push(T addend);

	int get_size() const;
	int get_capacity() const;

	T& operator[](int pos);

private:
	T *data = NULL;
	int capacity = 0;
	int size = 0;

};

// constructor

template <class T>
Vectors<T>::Vectors() {
	if (capacity > 0) delete[] data;
	data = new T[1];
	size = 0;
	capacity = 1;
}

template <class T>
Vectors<T>::Vectors(const Vectors<T> &p) {
	if (capacity > 0) {
		delete[] data;
	}
	data = new T[p.capacity];
	for (int i = 0; i < p.size; i++)
		data[i] = p.data[i];
	size = p.size;
	capacity = p.capacity;
	return *this;
}

template <class T>
void Vectors<T>::operator=(const Vectors<T> &p)
{
	if (capacity > 0)
		delete[] data;
	data = new T[p.capacity];
	for (int i = 0; i < p.size; i++)
		data[i] = p.data[i];
	size = p.size;
	capacity = p.capacity;
}

// deconstructor

template <class T>
Vectors<T>::~Vectors() {
	if (capacity > 0)
		delete[] data;
}

// functions

template <class T>
void Vectors<T>::clear() {
	if (capacity > 0)
		delete[] data;
	data = new T[1];
	size = 0;
	capacity = 1;
}

template <class T>
void Vectors<T>::fixedSize() {
	T* fixedData = new T[size];
	for (int i = 0; i < size; i++)
		fixedData[i] = data[i];
	if (capacity > 0)
		delete[] data;
	data = fixedData;
	capacity = size;
}


template <class T>
void Vectors<T>::push(T addend) {
	if (size + 1 > capacity) {
		T* old_data = data;
		data = new T[capacity * 2];
		for (int i = 0; i < size; i++)
			data[i] = old_data[i];
		capacity *= 2;
		if (size > 0)
			delete[] old_data;
	}

	data[size++] = addend;
}

template <class T>
int Vectors<T>::get_size() const {
	return size;
}

template <class T>
int Vectors<T>::get_capacity() const {
	return capacity;
}

template <class T>
T& Vectors<T>::operator[](int pos) {
	return data[pos];
}

template <class T>
std::ostream& operator<<(std::ostream& os, Vectors<T>& p) {
	for (int i = 0; i < p.get_size(); i++)
		os << p[i];
	return os;
}

