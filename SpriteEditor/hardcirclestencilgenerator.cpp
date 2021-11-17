/**
 * William Erignac
 * 11/10/21
 * @brief Creates a stencil of a circle
*/

#include "hardcirclestencilgenerator.h"
#include <math.h>

Pointer2DArray<float> HardCircleStencilGenerator::generate(unsigned int size)
{
	Pointer2DArray<float> stencil(size, size);

	float radius = (float)size/2;

	for (unsigned int i = 0; i < size; i++)
	{
		for (unsigned int j = 0; j < size; j++)
		{
			float distance = sqrt(pow(i - radius, 2) + pow(j - radius, 2));
			stencil[i][j] = (distance <= radius);
		}
	}

	return stencil;
}
