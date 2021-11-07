#ifndef UTILS_H
#define UTILS_H

#include <vector>

using std::vector;

class Utils {

public:
	template<typename T> // holy shiiiit
	static vector<T> join(vector<T> vector1, vector<T> vector2) {
		//for (int i = 0; i < vector2.size(); i++) {
		//	vector1.push_back(vector2[i]);
		//}
		//return vector1;
		vector1.insert(vector1.end(), vector2.begin(), vector2.end());
		return vector1; // append second vector at the end of the first vector, from range 0 - len of vector2
	}

	template<typename T>
	static vector<T> arrToVec(T* arr, unsigned int size) {
		vector<T> vec;
		for (int i = 0; i < size; i++) { // iterate through elements in array
			vec.push_back(*(arr[i])); // append each one to the vec
		}
		return vec;
	}

};

#endif