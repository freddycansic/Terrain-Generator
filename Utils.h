#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <random>
#include <time.h>

using std::vector;

namespace Globals {
	const unsigned int WIDTH = 1920, HEIGHT = 1080, VERTEX_LENGTH = 6;
};

namespace Utils { // namespace because im never going to create an instance of this if it were a class

	template<typename T>
	static vector<T> arrToVec(T* arr, size_t size) {
		vector<T> vec;
		for (int i = 0; i < size; i++) { // iterate through elements in array
			vec.push_back(*(arr[i])); // append each one to the vec
		}
		return vec;
	}

	template<typename T> // holy shiiiit
	static vector<T> join(vector<T> &vector1, const vector<T> &vector2) {
		vector1.insert(vector1.end(), vector2.begin(), vector2.end());
		return vector1; // append second vector at the end of the first vector, from range 0 - len of vector2
	}

	static float randf(float max) {
		return (float(rand()) / float((RAND_MAX)) * max);
	}

	template<typename T>
	static void printVec(const vector<T>& vec) {
		std::cout << "[";
		for (T element : vec) {
			std::cout << element << ", ";
		}
		std::cout << "]" <<std::endl;
	}

	static void printVertices(const vector<GLfloat>& vertices) {
		std::cout << "VERTICES" << std::endl;
		
		for (int i = 0; i < vertices.size() / Globals::VERTEX_LENGTH; i++) { // Mesh::VERTEX_LENGTH = position coords, color, texture coords
			for (int k = 0; k < Globals::VERTEX_LENGTH; k++) {
				std::cout << vertices[i * Globals::VERTEX_LENGTH + k] << ((k == 2) ? "  " : " "); // after pos coords do an extra space to show where the texture coords are also take any chance to use a ternary operator cause its so fucking cool
			}
			std::cout << std::endl;
		}
	}

	static void printIndices(const vector<GLuint>& indices) {
		std::cout << "INDICES" << std::endl;
		for (int i = 0; i < indices.size() / 3; i++) {
			for (int k = 0; k < 3; k++) {
				std::cout << indices[i * 3 + k] << " "; // after pos coords do an extra space to show where the texture coords are also take any chance to use a ternary operator cause its so fucking cool
			}
			std::cout << std::endl;
		}
	}

	template<typename T>
	static void printArr(const T* arr, size_t size) {
		std::cout << "[";
		for (int i = 0; i < size; i++) {
			std::cout << arr[i] << ", ";
		}
		std::cout << "]" << std::endl;
	}

	template<typename T>
	static T maxInVec(vector<T> vec) {
		T max = 0;
		for (T element : vec) {
			if (element > max){
				max = element;
			}
		}
		return max;
	}

	template<typename T>
	static vector<T> incrementAll(vector<T> vec, T increment) {
		vector<T> incrementedVec;
		for (T element : vec) {
			incrementedVec.push_back(element + increment);
		}
		return incrementedVec;
	}

	static vector<GLfloat> noiseGenerator(unsigned int permutations, unsigned int resolution, float max) {
		srand((unsigned int) time(NULL));
		
		vector<GLfloat> majorPoints;
		for (unsigned int i = 0; i < permutations; i++) {
			majorPoints.push_back((GLfloat)randf(max)); // populate major points with random values
		}

		//printVec(majorPoints);

		vector<GLfloat> allPoints;
		for (unsigned int i = 0; i < majorPoints.size(); i++) { // for every major point

			//std::cout << "majorPoints[" << i << "]" << std::endl;

			GLfloat currentPoint = majorPoints[i];
			if (i + 1 > (majorPoints.size() - 2)) return allPoints; // if next point is greater than the number of major points
			GLfloat nextPoint = majorPoints[i + 1];

			//std::cout << "Current point = " << currentPoint << std::endl;
			//std::cout << "Next point = " << nextPoint << std::endl;

			if (currentPoint < nextPoint) { // if current point is lower than next point 
				for (GLfloat k = currentPoint; // from the current point
					k < nextPoint; // to the next point
					k += (nextPoint - currentPoint) / resolution) { // increment by the difference / resolution e.g difference = 0.5, increment by 0.5/5 = 0.1 each time
						allPoints.push_back(k);
				}
			}
			else { // if current point is higher than the next point
				for (GLfloat k = currentPoint; k > nextPoint; k -= (currentPoint - nextPoint) / resolution) {
					allPoints.push_back(k);
				}
			}
		}
	}
};

#endif