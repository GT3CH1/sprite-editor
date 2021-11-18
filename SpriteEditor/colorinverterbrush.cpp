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
ColorInverterBrush::ColorInverterBrush(IStencilGenerator *generator) : PixelBrush(generator), coveredArea(0, 0)
{
}

/**
 * @brief Applies the tool size to the stencil and inverts the color of
 * each pixel.
 * @param canvasState Current ActionState of the frame
 * @param callbacks Current callback information
 */
void ColorInverterBrush::apply(ActionState &canvasState, const CallbackOptions &callbacks)
{
	setStencilOnSizeChange(canvasState.TOOL_SIZE);

	if (canvasState.NEW_STROKE)
		resetStroke(canvasState);

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
			QColor previousColor;
			float lastAmountInverted = 0;

			if (coveredArea[i + boundedArea.x()][j + boundedArea.y()].amountAffected > 0)
			{
				lastAmountInverted = coveredArea[i + boundedArea.x()][j + boundedArea.y()].amountAffected;
				previousColor = coveredArea[i + boundedArea.x()][j + boundedArea.y()].initialColor;
			}

			else
			{
				previousColor = pixelColors.pixelColor(boundedArea.x() + i, boundedArea.y() + j);
				coveredArea[i + boundedArea.x()][j + boundedArea.y()].initialColor = previousColor;
			}

			float amountToInvert = std::clamp(stencil[i + info.deltaX][j + info.deltaY] + lastAmountInverted, 0.0f, 1.0f);
			int invertedRedDifference = (255 - previousColor.red()) - previousColor.red();
			int invertedGreenDifference = 255 - previousColor.green() - previousColor.green();
			int invertedBlueDifference = 255 - previousColor.blue() - previousColor.blue();
			QColor weightedInvertedColor(previousColor.red() + invertedRedDifference * amountToInvert
										 , previousColor.green() + invertedGreenDifference * amountToInvert
										 , previousColor.blue() + invertedBlueDifference * amountToInvert
										 , previousColor.alpha());
			toReplace[i][j] = weightedInvertedColor;
			coveredArea[i + boundedArea.x()][j + boundedArea.y()].amountAffected = amountToInvert;
		}
	}

	callbacks.replacePixelColors(toReplace, boundedArea.x(), boundedArea.y());
}

/**
 * @brief Resets the stroke of this brush.
 * @param canvasState - The canvas state.
 */
void ColorInverterBrush::resetStroke(const ActionState &canvasState)
{
	Pointer2DArray<StrokeCovered> clearedArea(canvasState.ACTIVE_FRAME.width(), canvasState.ACTIVE_FRAME.height());
	coveredArea = clearedArea;
	StrokeCovered defaultStrokeCovered;
	defaultStrokeCovered.amountAffected = 0;
	QColor defaultColor;
	defaultStrokeCovered.initialColor = defaultColor;

	for (int  i = 0; i < (int)coveredArea.getWidth(); i++)
		for (int j = 0; j < (int)coveredArea.getHeight(); j++)
			coveredArea[i][j] = defaultStrokeCovered;
}
