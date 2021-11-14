#ifndef SQUARESTENCILGENERATOR_H
#define SQUARESTENCILGENERATOR_H

#include "istencilgenerator.h"


class SquareStencilGenerator : public IStencilGenerator
{
public:
	virtual void generate(int size, float** stencil);
};

#endif // SQUARESTENCILGENERATOR_H
