#ifndef PIXELERASER_H
#define PIXELERASER_H

#include "pixelbrush.h"
#include "istencilgenerator.h"

class PixelEraser : public PixelBrush
{
public:
	PixelEraser(IStencilGenerator *generate);
	virtual void apply(ActionState &canvasState, const CallbackOptions &callbacks);
};

#endif // PIXELERASER_H
