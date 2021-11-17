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
void PixelEraser::apply(ActionState& canvasState, const CallbackOptions& callbacks)
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

	bottomRightX = std::clamp(bottomRightX, 0, canvasState.ACTIVE_FRAME.width());
	bottomRightY = std::clamp(bottomRightY, 0, canvasState.ACTIVE_FRAME.height());

	unsigned int x = 0;
	unsigned int y = 0;
	unsigned int affectedWidth = 0;
	unsigned int affectedHeight = 0;

	if (upperLeftX > 0)
		x = upperLeftX;
	if (upperLeftY > 0)
		y = upperLeftY;

	affectedWidth = bottomRightX - x + (stencil.getWidth() % 2);
	affectedHeight = bottomRightY - y + (stencil.getHeight() % 2);

	int deltaX = x - upperLeftX;
	int deltaY = y - upperLeftY;

	Pointer2DArray<QColor> colors (affectedWidth, affectedHeight);

	for (unsigned int i = x - upperLeftX; i < colors.getWidth(); i++)
	{
		for (unsigned int j = y - upperLeftY; j < colors.getHeight(); j++)
		{
			float newAlpha = (1 - stencil[i + deltaX][j + deltaY]);
			QColor newColor(255, 255, 255, newAlpha*255);
			colors[i][j] = newColor;
		}
	}

	callbacks.setPixelColors(colors, x, y);
}
