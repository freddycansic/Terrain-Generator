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
		allXPoints.reserve(permutations * resolution);

		for (unsigned int i = 0; i < xMajorPoints.size()-1; i++) { // for every major point
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
				for (GLfloat current = (currentPoint - (currentPoint - nextPoint) / resolution); // starting 
					current > nextPoint; 
					currentPoint -= (currentPoint - nextPoint) / resolution) {

					print((current > nextPoint));
					allXPoints.push_back(current);
				}
			}
			else {
				for (GLfloat current = (currentPoint + (currentPoint - nextPoint) / resolution); 
					current < nextPoint;
					currentPoint += (nextPoint - currentPoint) / resolution) {

					allXPoints.push_back(current);
				}
			}

		}

		allXPoints.push_back(xMajorPoints[xMajorPoints.size() - 1]);
		
		allXPoints.shrink_to_fit();
		//std::cout << "COUNT = " << count << std::endl;
		//std::cout << "Count should be " << (((permutations - 1) * resolution) + 1) << std::endl;

		std::cout << "X MAJOR" << std::endl;
		Utils::printVec(xMajorPoints);
		std::cout << "X ALL" << std::endl;
		Utils::printVec(allXPoints);

		//******************************* GENERATE IN Z DIRECTION *******************************

		xMajorPoints.clear();
		xMajorPoints.shrink_to_fit();

		vector<GLfloat> zMajorPoints;
		zMajorPoints.reserve(permutations);

		for (unsigned int i = 0; i < permutations; i++) {
			zMajorPoints.push_back((GLfloat)randf(max)); // populate major points with random values
		}

		vector<GLfloat> allZPoints;
		allZPoints.reserve(permutations * resolution);

		for (unsigned int i = 0; i < zMajorPoints.size(); i++) { // for every major point
			allXPoints.push_back(zMajorPoints[i]);

			if (i + 1 == zMajorPoints.size()) break;

			GLfloat currentPoint = zMajorPoints[i];
			GLfloat nextPoint = zMajorPoints[i + 1];
			GLfloat increment = (nextPoint - currentPoint) / resolution;

			if (currentPoint > nextPoint) {
				for (GLfloat current = currentPoint + increment; current > nextPoint; currentPoint += increment) {
					allZPoints.push_back(current);
				}
			}
			else {
				for (GLfloat current = currentPoint + increment; current < nextPoint; currentPoint += increment) {
					allZPoints.push_back(current);
				}
			}
		}
		std::cout << "Z MAJOR" << std::endl;
		Utils::printVec(zMajorPoints);
		std::cout << "Z ALL" << std::endl;
		Utils::printVec(allZPoints);

		allZPoints.shrink_to_fit();

		vector<GLfloat> allPoints;
		allPoints.reserve(allXPoints.size() * allZPoints.size());

		allPoints = Utils::join(allPoints, allXPoints);

		//Utils::printVec(allPoints);

		
		std::cout << "ALL Z POINT SIZE" << allZPoints.size() << std::endl;
		for (unsigned int i = 1; i < allZPoints.size(); i++) {
			//std::cout << i << std::endl;
			vector<GLfloat> nextIncrementedXRow;
			nextIncrementedXRow.reserve(allXPoints.size());

			for (GLfloat element : allXPoints) {
				nextIncrementedXRow.push_back(element + allZPoints[i]);
			}

			allPoints = Utils::join(allPoints, nextIncrementedXRow);
		}

		//std::cout << "ALL POINTS" << std::endl;
		//Utils::printVec(allPoints);

		return allPoints;

	}
};

#endif