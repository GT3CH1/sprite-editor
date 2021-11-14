#ifndef SOFTCIRCLESTENCILGENERATOR_H
#define SOFTCIRCLESTENCILGENERATOR_H

#include "istencilgenerator.h"

class SoftCircleStencilGenerator : public IStencilGenerator
{
public:
	virtual Pointer2DArray<float> generate(unsigned int size);
};

#endif // SOFTCIRCLESTENCILGENERATOR_H
