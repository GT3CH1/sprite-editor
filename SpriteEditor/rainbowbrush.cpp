/**
 * William Erignac
 * 11/16/2021
 *
 * @brief The RainbowBrush class acts a a normal brush, but the color
 * is decided by progress through the rainbow as opposed to the tool color.
 */

#include "rainbowbrush.h"

/**
 * @brief Creates the RainbowBrush object
 * @param generator Pointer to the stencil needed for the tool
 */
RainbowBrush::RainbowBrush(IStencilGenerator *generator) : PixelBrush(generator)
{
}

/**
 * @brief Creates the RainbowBrush object with the given incrementPerCall (between 0 and 1).
 * @param generator Pointer to the stencil needed for the tool
 * @param _incrementPerCall The amount to advance in the rainbow as a percent between 0 and 1.
 */
RainbowBrush::RainbowBrush(IStencilGenerator *generator, float _incrementPerCall) : PixelBrush(generator), incrementPerCall(_incrementPerCall)
{
}

/**
 * @brief Applies the tool size to the stencil and paints a ranbow .
 * @param canvasState Current ActionState of the frame
 * @param callbacks Current callback information
 */
void RainbowBrush::apply(ActionState &canvasState, const CallbackOptions &callbacks)
{
	progress += incrementPerCall;

	while (progress >= 1)
		progress -= 1;

	QColor rainbowColor;
	rainbowColor.setHsv(360 * progress, canvasState.TOOL_COLOR.saturation(), canvasState.TOOL_COLOR.value(), canvasState.TOOL_COLOR.alpha());
	setStencilOnSizeChange(canvasState.TOOL_SIZE);
	BoundsInformation info;
	QRect boundedArea = ConstrainStencilBounds(stencil, canvasState.MOUSE_X_GRID_COORD, canvasState.MOUSE_Y_GRID_COORD,
						canvasState.ACTIVE_FRAME.width(), canvasState.ACTIVE_FRAME.height(),
						info);
	Pointer2DArray<QColor> toAdd(boundedArea.width(), boundedArea.height());

	for (unsigned int i = 0; i < toAdd.getWidth(); i++)
	{
		for (unsigned int j = 0; j < toAdd.getHeight(); j++)
		{
			float stencilAlpha = stencil[i + info.deltaX][j + info.deltaY];
			QColor newStencilColor(rainbowColor.red(), rainbowColor.green(), rainbowColor.blue(), rainbowColor.alpha() * stencilAlpha);
			toAdd[i][j] = newStencilColor;
		}
	}

	callbacks.paintPixelColors(toAdd, boundedArea.x(), boundedArea.y());
}
