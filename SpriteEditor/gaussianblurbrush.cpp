/**
 * William Erignac
 * 11/17/2021
 *
 * @brief The GaussianBlurBrush blurs the colors in its area of effect.
 */

#include "gaussianblurbrush.h"
#include "gaussianstencilgenerator.h"
#include <iostream>

/**
 * @brief Creates the ColorInverterBrush object
 * @param generator Pointer to the stencil needed for the tool
 */
GaussianBlurBrush::GaussianBlurBrush(IStencilGenerator* generator) : ColorInverterBrush(generator), gaussianStencil(0,0)
{	
	GaussianStencilGenerator gGenerator;
	gaussianStencil = gGenerator.generate(7);
}

/**
 * @brief Applies the tool size to the stencil and blurs
 * each pixel.
 * @param canvasState Current ActionState of the frame
 * @param callbacks Current callback information
 */
void GaussianBlurBrush::apply(ActionState& canvasState, const CallbackOptions& callbacks)
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

	for (int i = 0; i < (int) toReplace.getWidth(); i++)
	{
		for (int j = 0; j < (int) toReplace.getHeight(); j++)
		{
			QColor previousColor;
			float lastAmountBlurred = 0;
			//If we've already blurred this pixel, retrieve its original color and
			//the amount we've already blurred for accurate blurring.
			if(coveredArea[i + boundedArea.x()][j + boundedArea.y()].amountAffected > 0)
			{
				lastAmountBlurred = coveredArea[i + boundedArea.x()][j + boundedArea.y()].amountAffected;
				previousColor = coveredArea[i + boundedArea.x()][j + boundedArea.y()].initialColor;
			}
			else
			{ //If this is a pixel we haven't blurred yet, we can get its color from the canvas
			  //(lastAmountBlurred can stay zero since this pixel hasn't been blurred yet).
				previousColor = pixelColors.pixelColor(boundedArea.x() + i, boundedArea.y() + j);
				coveredArea[i + boundedArea.x()][j + boundedArea.y()].initialColor = previousColor;
			}

			float amountToBlur = std::clamp(stencil[i + info.deltaX][j + info.deltaY] + lastAmountBlurred, 0.0f, 1.0f);
			QColor mixedColor = collectBlurred(pixelColors, i + boundedArea.x(), j + boundedArea.y());
			QColor finalBlur(previousColor.red()*(1 - amountToBlur) + mixedColor.red()*amountToBlur,
							 previousColor.green()*(1 - amountToBlur) + mixedColor.green()*amountToBlur,
							 previousColor.blue()*(1 - amountToBlur) + mixedColor.blue()*amountToBlur,
							 previousColor.alpha()*(1 - amountToBlur) + mixedColor.alpha()*amountToBlur);
			toReplace[i][j] = finalBlur;
			coveredArea[i + boundedArea.x()][j + boundedArea.y()].amountAffected = amountToBlur;
		}
	}

	callbacks.replacePixelColors(toReplace, boundedArea.x(), boundedArea.y());
}

/**
 * @brief Aquires the blurred version of the given pixel using the gaussianStencil.
 * @param canvasColors The image that has the current pixel colors.
 * @param x The x coordinate of the pixel.
 * @param y The y corrdinate of the pixel.
 * @return The blurred version of the pixel.
 */
QColor GaussianBlurBrush::collectBlurred(QImage &canvasColors, int x, int y)
{
	int middleX = gaussianStencil.getWidth()/2;
	int middleY = gaussianStencil.getHeight()/2;

	float redSum = 0;
	float greenSum = 0;
	float blueSum = 0;
	float alphaSum = 0;

	for(int gaussX = 0; gaussX < (int) gaussianStencil.getWidth(); gaussX++)
	{
		for (int gaussY = 0; gaussY < (int) gaussianStencil.getHeight(); gaussY++)
		{
			float influence = gaussianStencil[gaussX][gaussY];
			//The location relative to the canvas of a pixel near the pixel at x,y
			int canvasX = x + (gaussX - middleX);
			int canvasY = y + (gaussY - middleY);
			//The color of this pixel before being blurred itself.
			QColor toMix;

			if(canvasX >= 0 && canvasX < canvasColors.width() && canvasY >= 0 && canvasY < canvasColors.height())
			{
				//If the pixel has not yet been blurred, we can use its canvas color.
				if (coveredArea[canvasX][canvasY].amountAffected == 0)
				{
					toMix = canvasColors.pixelColor(canvasX, canvasY);
				} //Otherwise, we have to use the color we stored while blurring.
				else
					toMix = coveredArea[canvasX][canvasY].initialColor;
			}
			else
			{ //If we are out of bounds, we use a tranparent white as a default color.
				QColor transWhite(255,255,255,0);
				toMix = transWhite;
			}

			redSum += influence * toMix.redF();
			greenSum += influence * toMix.greenF();
			blueSum += influence * toMix.blueF();
			alphaSum += influence * toMix.alphaF();
		}
	}

	QColor mixed(redSum*255, greenSum*255, blueSum*255, alphaSum*255);
	return mixed;
}
