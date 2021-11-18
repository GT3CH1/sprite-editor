/**
 * Kenzie Evans
 * William Erignac
 * 11/13/2021
 *
 * @brief The SprayCanBrush class creates a brush tool that applies the
 * current action state and callback information to the active frame.
 * It uses a stencil for a specific shape and then uses the colors to
 * apply the new color to the frame.
 */

#include "itool.h"
#include "spraycanbrush.h"
#include <algorithm>
#include <QPixmap>
#include <random>

/**
 * @brief Creates the SprayCanBrush object
 * @param generator Pointer to the stencil needed for the tool
 */
SprayCanBrush::SprayCanBrush(IStencilGenerator *generator) : stencilGenerator(generator), stencil(0, 0)
{
	srand(time(0));
}

/**
 * @brief Destroys this objects pointer to the stencil generator
 */
SprayCanBrush::~SprayCanBrush()
{
	delete stencilGenerator;
}

/**
 * @brief Creates a deep copy copy of another SprayCanBrush
 */
SprayCanBrush::SprayCanBrush(const SprayCanBrush &other) : stencil(other.stencil)
{
	*stencilGenerator = *other.stencilGenerator;
}

/**
 * @brief Creates a deep copy of another SprayCanBrush
 */
SprayCanBrush &SprayCanBrush::operator=(SprayCanBrush otherCopy)
{
	std::swap(stencil, otherCopy.stencil);
	std::swap(stencilGenerator, otherCopy.stencilGenerator);
	return *this;
}

/**
 * @brief Calculates the overlap between a stencil and a given area.
 * @param stencil The stencil (what would like to be drawn).
 * @param stencilCenterX The center of where the stencil would like to be applied.
 * @param stencilCenterY The center of where the stencil would like to be applied.
 * @param areaWidth The width of the bounding area (the frame in most cases).
 * @param areaHeight The height of the bounding area (the frame in most cases).
 * @param outInfo Information about what portion of stencil the bounding area covers.
 * @return A QRect that describes the bounded area relative to the bounding area.
 */
QRect SprayCanBrush::ConstrainStencilBounds(Pointer2DArray<float> stencil, int stencilCenterX, int stencilCenterY, int areaWidth, int areaHeight,  BoundsInformation &outInfo)
{
	int upperLeftX = stencilCenterX - stencil.getWidth() / 2;
	int upperLeftY = stencilCenterY - stencil.getHeight() / 2;
	int bottomRightX = stencilCenterX + stencil.getWidth() / 2;
	int bottomRightY = stencilCenterY + stencil.getHeight() / 2;
	bottomRightX = std::clamp(bottomRightX, 0, areaWidth);
	bottomRightY = std::clamp(bottomRightY, 0, areaHeight);
	unsigned int boundedAreaX = 0;
	unsigned int boundedAreaY = 0;
	unsigned int boundedAreaWidth = 0;
	unsigned int boundedAreaHeight = 0;

	if (upperLeftX > 0)
		boundedAreaX = upperLeftX;

	if (upperLeftY > 0)
		boundedAreaY = upperLeftY;

	boundedAreaWidth = bottomRightX - boundedAreaX + (stencil.getWidth() % 2);
	boundedAreaHeight = bottomRightY - boundedAreaY + (stencil.getHeight() % 2);
	int deltaX = boundedAreaX - upperLeftX;
	int deltaY = boundedAreaY - upperLeftY;
	outInfo.deltaX = deltaX;
	outInfo.deltaY = deltaY;
	QRect boundedArea(boundedAreaX, boundedAreaY, boundedAreaWidth, boundedAreaHeight);
	return boundedArea;
}

/**
 * @brief Applies the tool size to the stencil and the color to
 * each pixel.
 * @param canvasState Current ActionState of the frame
 * @param callbacks Current callback information
 */
void SprayCanBrush::apply(ActionState &canvasState, const CallbackOptions &callbacks)
{
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

			if (rndInt % 10 == 0)
				newStencilColor = QColor(canvasState.TOOL_COLOR.red(), canvasState.TOOL_COLOR.green(), canvasState.TOOL_COLOR.blue(), canvasState.TOOL_COLOR.alpha() * stencilAlpha);

			else if (rndInt % 5 == 1)
				newStencilColor = QColor(canvasState.TOOL_COLOR.red(), canvasState.TOOL_COLOR.green(), canvasState.TOOL_COLOR.blue(), canvasState.TOOL_COLOR.alpha() * stencilAlpha / (rand() % 4 + 1));

			toAdd[i][j] = newStencilColor;
		}
	}

	callbacks.paintPixelColors(toAdd, boundedArea.x(), boundedArea.y());
}
