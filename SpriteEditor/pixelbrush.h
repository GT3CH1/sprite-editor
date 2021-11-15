#ifndef PIXELBRUSH_H
#define PIXELBRUSH_H

#include "itool.h"
#include "istencilgenerator.h"

class PixelBrush : public ITool
{
public:
	PixelBrush(IStencilGenerator* generator);
	PixelBrush(const PixelBrush& other);
	PixelBrush& operator=(PixelBrush otherCopy);
	virtual ~PixelBrush();
	virtual void apply(ActionState& canvasState, const CallbackOptions& callbacks);
private:
	IStencilGenerator* stencilGenerator;
protected:
	Pointer2DArray<float> stencil;
	void setStencilOnSizeChange(unsigned int newSize);
};

#endif // PIXELBRUSH_H
