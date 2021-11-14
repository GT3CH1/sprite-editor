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
	setStencilOnSizeChange(canvasState.TOOL_SIZE);
	Pointer2DArray<QColor> colors (stencil.getWidth(), stencil.getHeight());

	unsigned int x = canvasState.MOUSE_X_GRID_COORD - stencil.getWidth() / 2;
	unsigned int y = canvasState.MOUSE_Y_GRID_COORD - stencil.getHeight() / 2;

	for (unsigned int i = 0; i < colors.getWidth(); i++)
	{
		for (unsigned int j = 0; j < colors.getHeight(); j++)
		{
			float stencilAlpha = stencil[i][j];
			QColor newStencilColor(canvasState.TOOL_COLOR.red(), canvasState.TOOL_COLOR.green(), canvasState.TOOL_COLOR.blue(), stencilAlpha * 255);
			colors[i][j] = computeColor(newStencilColor, canvasState.ACTIVE_LAYER.pixelColor(i+x,j+y));
		}
	}

	callbacks.setPixelColors(colors, x, y);
}

QColor PixelBrush::computeColor(QColor newColor, QColor lastColor)
{
	float combinedAlpha = newColor.alphaF() + lastColor.alphaF()*(1 - newColor.alphaF());
	float combinedR = (newColor.redF()*newColor.alphaF() + lastColor.redF()*lastColor.alphaF()*(1 - newColor.alphaF()))/combinedAlpha;
	float combinedG = (newColor.greenF()*newColor.alphaF() + lastColor.greenF()*lastColor.alphaF()*(1 - newColor.alphaF()))/combinedAlpha;
	float combinedB = (newColor.blueF()*newColor.alphaF() + lastColor.blueF()*lastColor.alphaF()*(1 - newColor.alphaF()))/combinedAlpha;
	QColor combinedColor(combinedR*255, combinedG*255, combinedB*255, combinedAlpha*255);
	return combinedColor;
}

void PixelBrush::setStencilOnSizeChange(unsigned int newSize)
{
	if (stencil.getHeight() != newSize)
		stencil = stencilGenerator->generate(newSize);
}
