/**
 * William Erignac
 * 11/16/2021
 *
 * @brief The ColorInverterBrush inverts the colors in its area of effect.
 */

#include "colorinverterbrush.h"

/**
 * @brief Creates the ColorInverterBrush object
 * @param generator Pointer to the stencil needed for the tool
 */
ColorInverterBrush::ColorInverterBrush(IStencilGenerator* generator) : PixelBrush(generator)
{

}

/**
 * @brief Applies the tool size to the stencil and inverts the color of
 * each pixel.
 * @param canvasState Current ActionState of the frame
 * @param callbacks Current callback information
 */
void ColorInverterBrush::apply(ActionState& canvasState, const CallbackOptions& callbacks)
{
	setStencilOnSizeChange(canvasState.TOOL_SIZE);

	BoundsInformation info;
	QRect boundedArea = ConstrainStencilBounds(stencil, canvasState.MOUSE_X_GRID_COORD, canvasState.MOUSE_Y_GRID_COORD,
														  canvasState.ACTIVE_FRAME.width(), canvasState.ACTIVE_FRAME.height(),
														  info);
	Pointer2DArray<QColor> toReplace(boundedArea.width(), boundedArea.height());

	QImage pixelColors = canvasState.ACTIVE_FRAME.toImage();

	for (unsigned int i = 0; i < toReplace.getWidth(); i++)
	{
		for (unsigned int j = 0; j < toReplace.getHeight(); j++)
		{
			float amountToInvert = stencil[i + info.deltaX][j + info.deltaY];
			QColor previousColor = pixelColors.pixelColor(boundedArea.x() + i, boundedArea.y() + j);

			int invertedRedDifference = (255 - previousColor.red()) - previousColor.red();
			int invertedGreenDifference = 255 - previousColor.green() - previousColor.green();
			int invertedBlueDifference = 255 - previousColor.blue() - previousColor.blue();

			QColor weightedInvertedColor(previousColor.red() + invertedRedDifference * amountToInvert
										 , previousColor.green() + invertedGreenDifference * amountToInvert
										 , previousColor.blue()+ invertedBlueDifference * amountToInvert
										 , previousColor.alpha());

			toReplace[i][j] = weightedInvertedColor;
		}
	}

	callbacks.replacePixelColors(toReplace, boundedArea.x(), boundedArea.y());
}
