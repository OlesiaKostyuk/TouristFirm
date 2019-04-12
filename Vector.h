#pragma once

template <class T>
class Vector {
	T* array;
	int size;
	int capacity;
public:
	Vector() {
		this->size = 0;
		this->capacity = 10;
		this->array = new T[capacity];
	}

	void add(T element) {
		if (size >= capacity) {
			capacity = capacity * 3 / 2 + 1;
			T* tempArray = new T[capacity];
			for (int i = 0; i < size; i++) {
				tempArray[i] = array[i];
			}
			delete[] array;
			array = tempArray;
		}
		array[size++] = element;
	}
	int getCapacity() { return this->capacity; }
	T* getArray() { return this->array; }
	int getSize() { return this->size; }
	~Vector() {
		delete[] this->array;
	};
};

