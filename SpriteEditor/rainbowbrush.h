#ifndef RAINBOWBRUSH_H
#define RAINBOWBRUSH_H

#include "pixelbrush.h"
#include "istencilgenerator.h"

class RainbowBrush : public PixelBrush
{
public:
	RainbowBrush(IStencilGenerator* generate);
	RainbowBrush(IStencilGenerator* generator, float _incrementPerCall);
	virtual void apply(ActionState& canvasState, const CallbackOptions& callbacks);
private:
	float progress = 0;
	float incrementPerCall = 0.01f;
};

#endif // RAINBOWBRUSH_H
