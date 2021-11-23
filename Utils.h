#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <array>
#include <cassert>

#define print(x) std::cout << x << std::endl;

using std::vector;
using std::array;

namespace Globals {
	const unsigned int WIDTH = 1920, HEIGHT = 1080, VERTEX_LENGTH = 6;
};

namespace Utils { // namespace because im never going to create an instance of this if it were a class

	template<typename T>
	static void freeVec(vector<T> vec) {
		vec.clear();
		vec.shrink_to_fit();
	}

	template<typename T>
	static vector<T> arrToVec(T* arr, size_t size) {
		vector<T> vec;
		vec.reserve(size);
		for (int i = 0; i < size; i++) { // iterate through elements in array
			vec.push_back(*(arr[i])); // append each one to the vec
		}
		return vec;
	}

	template<typename T> 
	static vector<T> join(vector<T> &vector1, const vector<T> &vector2) {
		vector1.reserve(vector2.size());

		for (const T& element : vector2) {
			vector1.push_back(element);
		}

		return vector1; // append second vector at the end of the first vector, from range 0 - len of vector2
	}

	template<typename T, size_t size>
	static vector<T> join(vector<T> &vector, const array<T, size> &array) {
		vector.reserve(array.size());

		for (const T& element : array) {
			vector.push_back(element);
		}

		return vector;
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
				std::cout << vertices[i * Globals::VERTEX_LENGTH + k] << ((k == 2) ? "  " : " "); // after pos coords do an extra space to show where the texture coords are also take any chance to use a ternary operator cause its so cool
			}
			std::cout << std::endl;
		}
	}

	static void printIndices(const vector<GLuint>& indices) {
		std::cout << "INDICES" << std::endl;
		for (int i = 0; i < indices.size() / 3; i++) {
			for (int k = 0; k < 3; k++) {
				std::cout << indices[i * 3 + k] << " "; // after pos coords do an extra space to show where the texture coords are also take any chance to use a ternary operator cause its so cool
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
	static vector<T> incrementAll(const vector<T>& vec, T increment) {
		vector<T> incrementedVec;
		incrementedVec.reserve(vec.size());

		for (T element : vec) {
			incrementedVec.push_back(element + increment);
		}
		return incrementedVec;
	}

	static vector<GLfloat> noiseGenerator(unsigned int permutations, unsigned int resolution, float max) {
		srand((unsigned int) time(NULL));
		
		//******************************* GENERATE IN X DIRECTION *******************************

		vector<GLfloat> xMajorPoints;
		xMajorPoints.reserve(permutations);

		for (unsigned int i = 0; i < permutations; i++) {
			xMajorPoints.push_back((GLfloat)randf(max)); // populate major points with random values
		}

		assert(xMajorPoints.size() == permutations);

		vector<GLfloat> allXPoints;
		allXPoints.reserve((permutations - 1) * resolution + 1);

		for (unsigned int i = 0; i < xMajorPoints.size(); i++) { // for every major point
			allXPoints.push_back(xMajorPoints[i]);
			
			if (i + 1 == xMajorPoints.size()) break;

			GLfloat currentPoint = xMajorPoints[i];
			GLfloat nextPoint = xMajorPoints[i+1];
			//GLfloat increment = (nextPoint - currentPoint) / resolution;

			print("CURRENT MAJOR = " << currentPoint);
			print("NEXT MAJOR = " << nextPoint);
			//print("INCREMENT = " << increment);

			print((nextPoint > currentPoint ? "NEXT HIGHER" : "NEXT LOWER"));

			if (currentPoint > nextPoint) { // if current point is higher than the next point
				GLfloat difference = currentPoint - nextPoint; // get the difference between both points
				GLfloat increment = difference / resolution; // split the difference into resolution pieces e.g 5 equal pieces

				for (GLfloat current = (currentPoint - increment); // starting point = current point - increment
					current >= nextPoint; // while the current point is greater than the next point
					current -= increment) { // decrement currentpoint

					allXPoints.push_back(current);
				}
			}
			else { // same but if current point is lower
				GLfloat difference = nextPoint - currentPoint;
				GLfloat increment = difference / resolution;

				for (GLfloat current = (currentPoint + increment); 
					current < nextPoint;
					current += increment) {
					
					allXPoints.push_back(current);
				}
			}

		}
		
		allXPoints.shrink_to_fit();

		std::cout << "X MAJOR" << std::endl;
		Utils::printVec(xMajorPoints);
		std::cout << "X ALL" << std::endl;
		Utils::printVec(allXPoints);

		Utils::freeVec(xMajorPoints);

		//******************************* GENERATE IN Z DIRECTION *******************************

		vector<GLfloat> zMajorPoints;
		zMajorPoints.reserve(permutations);

		for (unsigned int i = 0; i < permutations; i++) {
			zMajorPoints.push_back((GLfloat)randf(max)); // populate major points with random values
		}

		vector<GLfloat> allZPoints;
		allZPoints.reserve((permutations-1)*resolution + 1); // reserve space for all minor points. ((major points - the last point) * resolution aka inbetween places) + the final major point


		for (unsigned int i = 0; i < zMajorPoints.size(); i++) { // for every major point
			if (i == 0) {
				allZPoints.push_back(xMajorPoints[0]); // make first zmajor the first x major so lines sync up
			}
			else {
				allZPoints.push_back(zMajorPoints[i]);
			}

			if (i + 1 == zMajorPoints.size()) break;

			GLfloat currentPoint = zMajorPoints[i];
			GLfloat nextPoint = zMajorPoints[i + 1];
			//GLfloat increment = (nextPoint - currentPoint) / resolution;

			print("CURRENT MAJOR = " << currentPoint);
			print("NEXT MAJOR = " << nextPoint);
			//print("INCREMENT = " << increment);

			print((nextPoint > currentPoint ? "NEXT HIGHER" : "NEXT LOWER"));

			if (currentPoint > nextPoint) { // if current point is higher than the next point
				GLfloat difference = currentPoint - nextPoint; // get the difference between both points
				GLfloat increment = difference / resolution; // split the difference into resolution pieces e.g 5 equal pieces

				for (GLfloat current = (currentPoint - increment); // starting point = current point - increment
					current > nextPoint; // while the current point is greater than the next point
					current -= increment) { // decrement currentpoint

					allZPoints.push_back(current);
				}
			}
			else { // same but if current point is lower
				GLfloat difference = nextPoint - currentPoint;
				GLfloat increment = difference / resolution;

				for (GLfloat current = (currentPoint + increment);
					current < nextPoint;
					current += increment) {

					allZPoints.push_back(current);
				}
			}

		}

		allZPoints.shrink_to_fit();

		Utils::freeVec(xMajorPoints);

		std::cout << "Z MAJOR" << std::endl;
		Utils::printVec(zMajorPoints);
		std::cout << "Z ALL" << std::endl;
		Utils::printVec(allZPoints);

		vector<GLfloat> allPoints;
		allPoints.reserve(allXPoints.size() * allZPoints.size());

	
		// create all points using x and z axis

		for (unsigned int zRow = 0; zRow < allZPoints.size(); zRow++) { // for every point on the z axis

			for (unsigned int xPoint = 0; xPoint < allXPoints.size(); xPoint++) { // iterate through every point in the row
				
				allPoints.push_back(allXPoints[xPoint] + abs(allXPoints[xPoint] - allZPoints[zRow]));

			}

		}
		
		//unsigned int 
		//for (unsigned int i = 0; i < ((permutations - 1)*resolution + 1); i++) {
			

		//	print(std::endl);
		//}

		return allPoints;

	}
};

#endif