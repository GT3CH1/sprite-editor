/**
 * Kenzie Evans
 * William Erignac
 * 11/10/21
 * @brief Creates a square stencil
*/

#include "squarestencilgenerator.h"

void SquareStencilGenerator::generate(int size, float** stencil)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			stencil[i][j] = 1;
}
