/**
 * Kenzie Evans
 * William Erignac
 * 11/10/21
 * @brief Creates a circle stencil
*/


#include "softcirclestencilgenerator.h"
#include <math.h>

Pointer2DArray<float> SoftCircleStencilGenerator::generate(unsigned int size)
{
	Pointer2DArray<float> stencil(size, size);

	float radius = (float)size/2;

	for (unsigned int i = 0; i < size; i++)
	{
		for (unsigned int j = 0; j < size; j++)
		{
			float distance = sqrt(pow(i - radius, 2) + pow(j - radius, 2));
			if (distance > radius)
				stencil[i][j] = 0;
			else
				stencil[i][j] = sqrt(1 - pow(distance / radius, 2));
		}
	}

	return stencil;
}
