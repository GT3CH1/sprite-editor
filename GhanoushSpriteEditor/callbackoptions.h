#ifndef CALLBACKOPTIONS_H
#define CALLBACKOPTIONS_H

#include <QColor>
#include <functional>
#include "pointer2darray.h"

/**
 * William Erignac
 * 11/10/2021
 *
 * @brief The CallbackOptions struct is the means through which tools can affect the model.
 */
struct CallbackOptions
{
public:
	CallbackOptions(std::function<void(Pointer2DArray<QColor>, unsigned int, unsigned int)>,
					std::function<void(Pointer2DArray<QColor>, unsigned int, unsigned int)>);

	/**
	 * @brief A callback to paint the provided rectangle of colors on top of the
	 * existing pixels of the active frame.
	 * @param colors A rectangular, 2D array of colors.
	 * @param xCoord the displacement of the pixels to be added in the x direction
	 * (x coordinate of upper left pixel in 2D array).
	 * @param yCoord the  displacement of the pixels to be added in the y direction
	 * (y coordinate of upper left pixel in 2D array).
	 */
	std::function<void(Pointer2DArray<QColor>, unsigned int, unsigned int)> paintPixelColors;

	/**
	 * @brief A callback to replace the colors of pixels on the current frame
	 * with new colors.
	 * @param colors A rectangular, 2D array of colors.
	 * @param xCoord the displacement of the pixels to be set in the x direction
	 * (x coordinate of upper left pixel in 2D array).
	 * @param yCoord the  displacement of the pixels to be set in the y direction
	 * (y coordinate of upper left pixel in 2D array).
	 */
	std::function<void(Pointer2DArray<QColor>, unsigned int, unsigned int)> replacePixelColors;
};
#endif // CALLBACKOPTIONS_H
