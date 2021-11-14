#ifndef ISTENCILGENERATOR_H
#define ISTENCILGENERATOR_H

#include "pointer2darray.h"

/**
 * Kenzie Evans
 * William Erignac
 * 11/10/2021
 *
 * @brief The IStencilGenerator class generates stencils for tools to use.
 */
class IStencilGenerator
{
public:
	/**
	 * @brief Fills the stencil parameter with weights representing this generator's shape.
	 * @param size The size of the stencil to fill.
	 */
	virtual Pointer2DArray<float> generate(unsigned int size) = 0;
};

#endif // ISTENCILGENERATOR_H
