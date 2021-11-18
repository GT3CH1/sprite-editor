/**
 * Kenzie Evans
 * William Erignac
 * 11/10/21
 * @brief Creates a square stencil
*/

#include "squarestencilgenerator.h"

Pointer2DArray<float> SquareStencilGenerator::generate(unsigned int size)
{
	Pointer2DArray<float> stencil(size, size);
	for (unsigned int i = 0; i < size; i++)
		for (unsigned int j = 0; j < size; j++)
			stencil[i][j] = 1;
	return stencil;
}
