/**
 * William Erignac
 * 11/17/21
 * @brief Creates a stencil of a gaussian curve
*/


#include "gaussianstencilgenerator.h"
#include <math.h>
#include <iostream>

float normCDF(float a, float b)
{
	return (std::erf(b) + 1 - (std::erf(a) + 1))/2;
}

Pointer2DArray<float> GaussianStencilGenerator::generate(unsigned int size)
{
	Pointer2DArray<float> stencil(size, size);

	float radius = (float)size/2;

	float sum = 0;

	for (int i = 0; i < (int)size; i++)
	{
		for (int j = 0; j < (int)size; j++)
		{
            float leftX = i - radius;
            float rightX = i + 1 - radius;

            float upY = j - radius;
            float downY = j + 1 - radius;

			float factorX = normCDF(leftX, rightX);
            float factorY = normCDF(upY, downY);

			std::cout << factorX * factorY;
			sum += factorX * factorY;
			stencil[i][j] = factorX * factorY;
		}
		std::cout << std::endl;
	}

	std::cout << sum << std::endl;

	return stencil;
}
