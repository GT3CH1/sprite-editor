//#include "squarestencilgenerator.h"
//#include "softcirclestencilgenerator.h"
#include "pointer2darray.h"
#include "pointer2darray.cpp"

#include <iostream>
int test() {

	// lines 6 - 12 and 20 - 22 are from
	// https://www.techiedelight.com/pass-2d-array-function-parameter/
	int size = 2;
	//rows
	float** square = (float**)malloc(size * sizeof(float*));

	for (int i = 0; i < size; i++)
		square[i] = (float*)malloc(size * sizeof(float));

//	SquareStencilGenerator q;
//	q.generate(size, square);

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			std::cout << square[i][j] << std::endl;

	int sizeC = 20;
	//rows
	float** circle = (float**)malloc(sizeC * sizeof(float*));

	for (int i = 0; i < sizeC; i++)
		circle[i] = (float*)malloc(sizeC * sizeof(float));

//	SoftCircleStencilGenerator c;
//	c.generate(sizeC, circle);

	for (int i = 0; i < sizeC; i++)
	{
		for (int j = 0; j < sizeC; j++)
			std::cout << circle[i][j] << " ";
		std::cout << std::endl;
	}

	for (int i = 0; i < size; i++)
		free(square[i]);
	free(square);

	for (int i = 0; i < size; i++)
		free(circle[i]);
	free(circle);
	return 1;
}

int testPointerArray() {

	unsigned int height = 3;
	unsigned int width = 3;
	Pointer2DArray<float> p (width, height);
	std::cout<< p.getHeight() << std::endl;
	std::cout<< p.getWidth() << std::endl;

	for (unsigned int i = 0; i < width; i++)
		for (unsigned int j = 0; j < height; j++)
			p[i][j] = i + j;

	for (unsigned int i = 0; i < width; i++) {
		for (unsigned int j = 0; j < height; j++)
			std::cout << p[i][j];
		std::cout << std::endl;
	}

	Pointer2DArray<float> q = p;
	for (unsigned int i = 0; i < width; i++) {
		for (unsigned int j = 0; j < height; j++)
			std::cout << q[i][j];
		std::cout << std::endl;
	}

	for (unsigned int i = 0; i < width; i++)
		for (unsigned int j = 0; j < height; j++)
			p[i][j] = 0;
	for (unsigned int i = 0; i < width; i++) {
		for (unsigned int j = 0; j < height; j++)
			std::cout << p[i][j];
		std::cout << std::endl;
	}
	for (unsigned int i = 0; i < width; i++) {
		for (unsigned int j = 0; j < height; j++)
			std::cout << q[i][j];
		std::cout << std::endl;
	}


	return 1;
}
