#ifndef COLORINVERTERBRUSH_H
#define COLORINVERTERBRUSH_H

#include "pixelbrush.h"
#include "istencilgenerator.h"

class ColorInverterBrush : public PixelBrush
{
public:
	ColorInverterBrush(IStencilGenerator* generate);
	virtual void apply(ActionState& canvasState, const CallbackOptions& callbacks);
};


#endif // COLORINVERTERBRUSH_H
