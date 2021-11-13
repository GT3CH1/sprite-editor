/**
 * Kenzie Evans
 * 11/13/21
 * */

#ifndef PIXELBRUSH_H
#define PIXELBRUSH_H

#include "itool.h"

class PixelBrush : public ITool
{
public:
//	PixelBrush(StencilGenerator generator);
	virtual void apply(const ActionState& canvasState, const CallbackOptions& callbacks);
private:
//	StencilGenerator stencilGenerator;
protected:
//	float[][] stencil;
	void setStencilOnSizeChange(int newSize);
};

#endif // PIXELBRUSH_H
