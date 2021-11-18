/**
 * Kenzie Evans
 * 11/17/2021
 *
 * @brief The SprayCanBrush class creates a brush tool that applies the
 * current action state and callback information to the active frame.
 * It uses a stencil for a specific shape and then uses the colors to
 * apply the new color to the frame.
 * */

#include "rainbowspraycanbrush.h"

/**
 * @brief Creates a spray can tool that sprays rainbow colors
 * @param generator
 */
RainBowSprayCanBrush::RainBowSprayCanBrush(IStencilGenerator* generator) : SprayCanBrush(generator)
{
}

/**
 * @brief Applies the tool size to the stencil and the color to
 * each pixel.
 * @param canvasState Current ActionState of the frame
 * @param callbacks Current callback information
 */
void RainBowSprayCanBrush::apply(ActionState& canvasState, const CallbackOptions& callbacks)
{
	progress += incrementPerCall;
	while(progress >= 1)
		progress -= 1;
	QColor rainbowColor;
	rainbowColor.setHsv(360 * progress,canvasState.TOOL_COLOR.saturation(),canvasState.TOOL_COLOR.value(),canvasState.TOOL_COLOR.alpha());
	stencil = stencilGenerator->generate(canvasState.TOOL_SIZE);
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
			QColor newStencilColor(0, 0, 0, 0);
			int rndInt = rand();
			if(rndInt%10 == 0)
				newStencilColor = QColor(rainbowColor.red(), rainbowColor.green(), rainbowColor.blue(), rainbowColor.alpha() * stencilAlpha);
			else if(rndInt%5 == 1)
				newStencilColor = QColor(rainbowColor.red(), rainbowColor.green(), rainbowColor.blue(), rainbowColor.alpha() * stencilAlpha / (rand()%4 + 1));
			toAdd[i][j] = newStencilColor;
		}
	}
	callbacks.paintPixelColors(toAdd, boundedArea.x(), boundedArea.y());
}

