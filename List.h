#ifndef LIST_H
#define LIST_H

#include <vector>

using std::vector;

template<typename T> // holy shiiiit
class List
{
public:
	List(T* arr, unsigned int size);
	List append(List& other);

private:
	vector<T> elements;
	static vector<T> join(vector<T> vector1, vector<T> vector2); 

};

#endif

