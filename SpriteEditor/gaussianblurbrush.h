#ifndef GAUSSINBLURBRUSH_H
#define GAUSSINBLURBRUSH_H

#include "colorinverterbrush.h"
#include "istencilgenerator.h"

class GaussianBlurBrush : public ColorInverterBrush
{
private:
	Pointer2DArray<float> gaussianStencil;
	QColor collectBlurred(QImage& canvasColors, int x, int y);

public:
	GaussianBlurBrush(IStencilGenerator* generate);
	virtual void apply(ActionState& canvasState, const CallbackOptions& callbacks);
};


#endif // GAUSSINBLURBRUSH_H
