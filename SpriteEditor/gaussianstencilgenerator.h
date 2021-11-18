#ifndef GAUSSIANSTENCILGENERATOR_H
#define GAUSSIANSTENCILGENERATOR_H

#include "istencilgenerator.h"

class GaussianStencilGenerator : public IStencilGenerator
{
public:
	virtual Pointer2DArray<float> generate(unsigned int size);
};

#endif // GAUSSIANSTENCILGENERATOR_H
