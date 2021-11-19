#ifndef RAINBOWBRUSH_H
#define RAINBOWBRUSH_H

#include "pixelbrush.h"
#include "istencilgenerator.h"

class RainbowBrush : public PixelBrush
{
private:
	float progress = 0;
	float incrementPerCall = 0.01f;
public:
	RainbowBrush(IStencilGenerator *generate);
	RainbowBrush(IStencilGenerator *generator, float _incrementPerCall);
	virtual void apply(ActionState &canvasState, const CallbackOptions &callbacks);
};

#endif // RAINBOWBRUSH_H
