/**
 * William Erignac
 * 11/10/21
 * @brief Creates a stencil of a circle
*/

#include "hardcirclestencilgenerator.h"
#include <math.h>

/**
 * @brief Generates a hard circle given the size.
 * @param size - The size of circle to generate.
 * @return A Pointer2DArray of coordinates for a circle.
 */
Pointer2DArray<float> HardCircleStencilGenerator::generate(unsigned int size)
{
	Pointer2DArray<float> stencil(size, size);
	float radius = (float)size / 2;

	for (int i = 0; i < (int)size; i++)
	{
		for (int j = 0; j < (int)size; j++)
		{
			float distance = sqrt(pow(i - radius, 2) + pow(j - radius, 2));
			stencil[i][j] = (distance <= radius);
		}
	}

	return stencil;
}
