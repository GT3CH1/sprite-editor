#ifndef SOFTCIRCLESTENCILGENERATOR_H
#define SOFTCIRCLESTENCILGENERATOR_H

#include "istencilgenerator.h"

class SoftCircleStencilGenerator : public IStencilGenerator
{
public:
	virtual void generate(int size, float** stencil);
};

#endif // SOFTCIRCLESTENCILGENERATOR_H
