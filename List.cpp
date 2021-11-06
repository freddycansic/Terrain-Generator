#include "List.h"

template<typename T>
unsigned int List<T>::length() {
	return sizeof(this) / sizeof(T);
}

template<typename T>
vector<T> List<T>::join(vector<T> vector1, vector<T> vector2) {
	return vector1.insert(vector1.end, vector2.begin(), vector2.end()); // append second vector at the end of the first vector, from range 0 - len of vector2
}

template<typename T>
List<T>::List(T* arr, unsigned int size) {
	vector<T> vec;
	for (int i = 0; i < size; i++) {
		vec.push_back(*(arr[i]));
	}
	this->elements = vec;
}

template<typename T>
GLfloat List<T>::toGLFloatArr() {
	//GLFloat* newArr = new GLFloat[this->length()];

}