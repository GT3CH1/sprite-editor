#ifndef SQUARESTENCILGENERATOR_H
#define SQUARESTENCILGENERATOR_H

#include "istencilgenerator.h"


class SquareStencilGenerator : public IStencilGenerator
{
public:
	virtual Pointer2DArray<float> generate(unsigned int size);
};

#endif // SQUARESTENCILGENERATOR_H
