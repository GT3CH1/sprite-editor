/**
 * Kenzie Evans
 * William Erignac
 * 11/13/2021
 *
 * @brief The PixelEraser class creates an eraser tool that applies the
 * current action state and callback information to the active frame.
 * It uses a stencil for a specific shape.
 */

#include "pixeleraser.h"
/**
 * @brief Creates the PixelEraser object
 * @param generator Pointer to the stencil needed for the tool
 */
PixelEraser::PixelEraser(IStencilGenerator* generator) : PixelBrush(generator)
{

}

/**
 * @brief Applies the tool size to the stencil and erases the color of
 * each pixel.
 * @param canvasState Current ActionState of the frame
 * @param callbacks Current callback information
 */
void PixelEraser::apply(const ActionState& canvasState, const CallbackOptions& callbacks)
{
	setStencilOnSizeChange(canvasState.TOOL_SIZE);
	/* Out-of-bounds culling (getting rid of parts of the
	 * brush that are outside the bounds of the canvas).
	 * TODO(werignac-utah): Replace this with a helper method.
	 */
	int upperLeftX = canvasState.MOUSE_X_GRID_COORD - stencil.getWidth() / 2;
	int upperLeftY = canvasState.MOUSE_Y_GRID_COORD - stencil.getHeight() / 2;

	int bottomRightX = canvasState.MOUSE_X_GRID_COORD + stencil.getWidth() / 2;
	int bottomRightY = canvasState.MOUSE_Y_GRID_COORD + stencil.getHeight() / 2;

	bottomRightX = std::clamp(bottomRightX, 0, canvasState.ACTIVE_LAYER.width());
	bottomRightY = std::clamp(bottomRightY, 0, canvasState.ACTIVE_LAYER.height());

	unsigned int x = 0;
	unsigned int y = 0;
	unsigned int affectedWidth = 0;
	unsigned int affectedHeight = 0;

	if (upperLeftX > 0)
		x = upperLeftX;
	if (upperLeftY > 0)
		y = upperLeftY;

	affectedWidth = bottomRightX - upperLeftX;
	affectedHeight = bottomRightY - upperLeftY;

	Pointer2DArray<QColor> colors (affectedWidth, affectedHeight);

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
