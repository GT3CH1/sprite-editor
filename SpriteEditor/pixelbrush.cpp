#include "itool.h"
#include "pixelbrush.h"

PixelBrush::PixelBrush(IStencilGenerator* generator) : stencilGenerator(generator), stencil(0,0)
{
}

PixelBrush::~PixelBrush()
{
	delete stencilGenerator;
}

PixelBrush::PixelBrush(const PixelBrush& other) : stencil(other.stencil)
{
	*stencilGenerator = *other.stencilGenerator;
}

PixelBrush& PixelBrush::operator=(PixelBrush otherCopy)
{
	std::swap(stencil, otherCopy.stencil);
	std::swap(stencilGenerator, otherCopy.stencilGenerator);
	return *this;

}

void PixelBrush::apply(const ActionState& canvasState, const CallbackOptions& callbacks)
{

}

void PixelBrush::setStencilOnSizeChange(int newSize)
{

}
