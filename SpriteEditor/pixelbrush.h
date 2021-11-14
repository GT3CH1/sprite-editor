/**
 * Kenzie Evans
 * 11/13/21
 * */

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
	virtual void apply(const ActionState& canvasState, const CallbackOptions& callbacks);
private:
	IStencilGenerator* stencilGenerator;
protected:
	Pointer2DArray<float> stencil;
	void setStencilOnSizeChange(unsigned int newSize);
	QColor computeColor(QColor newColor, QColor lastColor);
};

#endif // PIXELBRUSH_H
