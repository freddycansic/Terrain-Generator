#include "Utils.h"

template<typename T>
vector<T> Utils::join(vector<T> vector1, vector<T> vector2) {
	return vector1.insert(vector1.end, vector2.begin(), vector2.end()); // append second vector at the end of the first vector, from range 0 - len of vector2
}

template<typename T>
vector<T> Utils::arrToVec(T* arr, unsigned int size) {
	vector<T> vec;
	for (int i = 0; i < size; i++) { // iterate through elements in array
		vec.push_back(*(arr[i])); // append each one to the vec
	}
	return vec;
}