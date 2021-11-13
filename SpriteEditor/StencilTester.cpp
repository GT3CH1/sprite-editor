//#include "squarestencilgenerator.h"
//#include "softcirclestencilgenerator.h"

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
