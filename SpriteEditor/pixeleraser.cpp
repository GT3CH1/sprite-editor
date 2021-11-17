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

	BoundsInformation info;
	QRect boundedArea = ConstrainStencilBounds(stencil, canvasState.MOUSE_X_GRID_COORD, canvasState.MOUSE_Y_GRID_COORD,
														  canvasState.ACTIVE_FRAME.width(), canvasState.ACTIVE_FRAME.height(),
														  info);
	Pointer2DArray<QColor> toReplace(boundedArea.width(), boundedArea.height());

	for (unsigned int i = 0; i < toReplace.getWidth(); i++)
	{
		for (unsigned int j = 0; j < toReplace.getHeight(); j++)
		{
			float newAlpha =  stencil[i + info.deltaX][j + info.deltaY];
			QColor newColor(255, 255, 255, newAlpha*255);
			toReplace[i][j] = newColor;
		}
	}

	callbacks.replacePixelColors(toReplace, boundedArea.x(), boundedArea.y());
}
