#ifndef HARDCIRCLESTENCILGENERATOR_H
#define HARDCIRCLESTENCILGENERATOR_H

#include "istencilgenerator.h"

class HardCircleStencilGenerator : public IStencilGenerator
{
public:
	virtual Pointer2DArray<float> generate(unsigned int size);
};

#endif // HARDCIRCLESTENCILGENERATOR_H
