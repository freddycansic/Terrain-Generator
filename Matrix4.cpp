#include "Matrix4.h"

Matrix4::Matrix4(int arr[16]) {
	for (int i = 0; i < 16; i++) {
		this->matrix[i] = arr[i];
	}
}

void Matrix4::print() {
	for (int i = 0; i < 4; i++) { // for each row
		for (int k = 0; k < 4; k++) { // print each element
			std::cout << this->matrix[k] << " ";
		}
		std::cout << std::endl;
	}
}