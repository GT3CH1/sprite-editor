/**
 * Kenzie Evans
 * William Erignac
 * 11/13/2021
 *
 * @brief The PixelBrush class creates a brush tool that applies the
 * current action state and callback information to the active frame.
 * It uses a stencil for a specific shape and then uses the colors to
 * apply the new color to the frame.
 */

#include "itool.h"
#include "pixelbrush.h"
#include <algorithm>
#include <QPixmap>

/**
 * @brief Creates the PixelBrush object
 * @param generator Pointer to the stencil needed for the tool
 */
PixelBrush::PixelBrush(IStencilGenerator* generator) : stencilGenerator(generator), stencil(0,0)
{
}

/**
 * @brief Destroys this objects pointer to the stencil generator
 */
PixelBrush::~PixelBrush()
{
	delete stencilGenerator;
}

/**
 * @brief Creates a deep copy copy of another PixelBrush
 */
PixelBrush::PixelBrush(const PixelBrush& other) : stencil(other.stencil)
{
	*stencilGenerator = *other.stencilGenerator;
}

/**
 * @brief Creates a deep copy of another PixelBrush
 */
PixelBrush& PixelBrush::operator=(PixelBrush otherCopy)
{
	std::swap(stencil, otherCopy.stencil);
	std::swap(stencilGenerator, otherCopy.stencilGenerator);
	return *this;
}

/**
 * @brief Applies the tool size to the stencil and the color to
 * each pixel.
 * @param canvasState Current ActionState of the frame
 * @param callbacks Current callback information
 */
void PixelBrush::apply(ActionState& canvasState, const CallbackOptions& callbacks)
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

	affectedWidth = bottomRightX - upperLeftX;
	affectedHeight = bottomRightY - upperLeftY;

	Pointer2DArray<QColor> colors (affectedWidth, affectedHeight);

	for (unsigned int i = x - upperLeftX; i < colors.getWidth(); i++)
	{
		for (unsigned int j = y - upperLeftY; j < colors.getHeight(); j++)
		{
			float stencilAlpha = stencil[i + upperLeftX][j + upperLeftY];
			QColor newStencilColor(canvasState.TOOL_COLOR.red(), canvasState.TOOL_COLOR.green(), canvasState.TOOL_COLOR.blue(), stencilAlpha * 255);
			colors[i][j] = newStencilColor;
		}
	}

	callbacks.paintPixelColors(colors, x, y);
}

/**
 * @brief Sets the size of the stencil.
 * @param newSize Size of the brush
 */
void PixelBrush::setStencilOnSizeChange(unsigned int newSize)
{
	if (stencil.getHeight() != newSize)
		stencil = stencilGenerator->generate(newSize);
}
