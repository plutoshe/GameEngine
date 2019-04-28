#pragma once
#include <iostream>
#include "Log.h"
namespace DataStructure {
	template<class T>
	class List
	{
	public:
		//TODO: add ...param to construct list
		List();
		List(const List<T> &p);
		void operator=(const List<T> &p);

		~List();

		void clear();
		void fixedSize();
		void push(T addend);
		void remove(int _index, int _size);
		void remove(int _index);

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
	List<T>::List() {
		if (capacity > 0) delete[] data;
		data = new T[1];
		size = 0;
		capacity = 1;
	}

	template <class T>
	List<T>::List(const List<T> &p) {
		if (capacity > 0) {
			delete[] data;
		}
		data = new T[p.capacity];
		for (int i = 0; i < p.size; i++)
			data[i] = p.data[i];
		size = p.size;
		capacity = p.capacity;
	}

	template <class T>
	void List<T>::operator=(const List<T> &p)
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
	List<T>::~List() {
		if (capacity > 0)
			delete[] data;
	}

	// functions

	template <class T>
	void List<T>::clear() {
		if (capacity > 0)
			delete[] data;
		data = new T[1];
		size = 0;
		capacity = 1;
	}
	template <class T>
	void List<T>::remove(int _index) {
		remove(_index, 1);
	}

	template <class T>
	void List<T>::remove(int _index, int _size) {
		for (int i = _index; i < size - _size; i++) 
			data[i] = data[i + _size];
		for (int i = size - _size; i < size; i++)
			data[i] = nullptr;
		size -= _size;
	}

	template <class T>
	void List<T>::fixedSize() {
		T* fixedData = new T[size];
		for (int i = 0; i < size; i++)
			fixedData[i] = data[i];
		if (capacity > 0)
			delete[] data;
		data = fixedData;
		capacity = size;
	}


	template <class T>
	void List<T>::push(T addend) {
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
	int List<T>::get_size() const {
		return size;
	}

	template <class T>
	int List<T>::get_capacity() const {
		return capacity;
	}

	template <class T>
	T& List<T>::operator[](int pos) {
		return data[pos];
	}

	template <class T>
	std::ostream& operator<<(std::ostream& os, List<T>& p) {
		for (int i = 0; i < p.get_size(); i++)
			os << p[i];
		return os;
	}


}