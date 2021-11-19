#ifndef RAINBOWSPRAYCANBRUSH_H
#define RAINBOWSPRAYCANBRUSH_H

#include "spraycanbrush.h"

class RainBowSprayCanBrush : public SprayCanBrush
{
private:
	float progress = 0;
	float incrementPerCall = 0.01f;
public:
	RainBowSprayCanBrush(IStencilGenerator* generate);
	virtual void apply(ActionState& canvasState, const CallbackOptions& callbacks);
};

#endif // RAINBOWSPRAYCANBRUSH_H
