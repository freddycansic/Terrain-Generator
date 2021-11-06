#ifndef UTILS_H
#define UTILS_H

#include <vector>

using std::vector;

class Utils {

public:
	template<typename T> // holy shiiiit
	static vector<T> join(vector<T> vector1, vector<T> vector2);

	template<typename T>
	static vector<T> arrToVec(T* arr, unsigned int size);

};

#endif