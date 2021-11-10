#ifndef CALLBACKOPTIONS_H
#define CALLBACKOPTIONS_H

#include <QColor>

///
/// \brief The CallbackOptions struct is the means through which tools can affect the model.
///
struct CallbackOptions
{
public:
	CallbackOptions(void (*_setPixelColors)(QColor**, unsigned int width, unsigned int height, unsigned int xCoord, unsigned int yCoord),
					void (*_setPixelColor)(QColor, unsigned int xCoord, unsigned int yCoord));
	//https://stackoverflow.com/questions/10003270/gcc-array-type-has-incomplete-element-type


	///
	/// \param QColor** a rectangular, 2D array of colors.
	/// \param width the 2D array of colors.
	/// \param height of the 2D array of colors.
	///	\param xCoord the displacement of the pixels to be set in the x direction
	///		(x coordinate of upper left pixel in 2D array).
	/// \param yCoord the  displacement of the pixels to be set in the y direction
	///		(y coordinate of upper left pixel in 2D array).
	///
	void (*setPixelColors)(QColor**, uint width, uint height, unsigned int xCoord, unsigned int yCoord);

	///
	/// \param QColor the color to set the given pixel.
	/// \param width the x coordinate of the pixel.
	/// \param height the y coordinate of the pixel.
	///
	void (*setPixelColor)(QColor, unsigned int xCoord, unsigned int yCoord);
};

#endif // CALLBACKOPTIONS_H
