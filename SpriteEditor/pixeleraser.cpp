#include "pixeleraser.h"

PixelEraser::PixelEraser(IStencilGenerator* generator) : PixelBrush(generator)
{

}

void PixelEraser::apply(const ActionState& canvasState, const CallbackOptions& callbacks)
{
	setStencilOnSizeChange(canvasState.TOOL_SIZE);
	Pointer2DArray<QColor> colors (stencil.getWidth(), stencil.getHeight());

	unsigned int x = canvasState.MOUSE_X_GRID_COORD - stencil.getWidth() / 2;
	unsigned int y = canvasState.MOUSE_Y_GRID_COORD - stencil.getHeight() / 2;

	for (unsigned int i = 0; i < colors.getWidth(); i++)
	{
		for (unsigned int j = 0; j < colors.getHeight(); j++)
		{
			QColor oldColor = canvasState.ACTIVE_LAYER.pixelColor(x + i, y + j);
			float newAlpha = oldColor.alphaF()*(1 - stencil[i][j]);
			QColor newColor(oldColor.red(), oldColor.green(), oldColor.blue(), newAlpha*255);
			colors[i][j] = newColor;
		}
	}

	callbacks.setPixelColors(colors, x, y);
}
