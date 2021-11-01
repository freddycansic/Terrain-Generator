#ifndef MATRIX_4_H
#define MATRIX_4_H

#include <iostream>

class Matrix4 {

public:
	int matrix[16];

	Matrix4(int arr[16]);
	
	void print();
};

#endif