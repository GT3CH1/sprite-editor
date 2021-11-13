#ifndef PIXELERASER_H
#define PIXELERASER_H

#include "pixelbrush.h"

class PixelEraser : public PixelBrush
{
public:
//	PixelEraser(StencilGenerator generate);
	virtual void apply(const ActionState& canvasState, const CallbackOptions& callbacks);
};

#endif // PIXELERASER_H
