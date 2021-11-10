//TODO(gcpease): Remove this file when done
#include "callbackoptions.h"
#include <iostream>
#include <string>

void setPixel(QColor color, unsigned int xCoord, unsigned int yCoord)
{
	std::cout << "Pixel (" << xCoord << ", " << yCoord << ") is being set to" << "(" +  color.red() << ", " + color.blue() << ", " + color.green() << ")" << std::endl;
}

void setPixels(QColor** color, unsigned int width, unsigned int height, unsigned int xCoord, unsigned int yCoord)
{
	std::cout <<"Pixels from " << xCoord << " to " << xCoord + width << " and " << yCoord << " to " << yCoord + height << std::endl;
}

int main()
{
	CallbackOptions option(setPixels, setPixel);

	QColor color = QColor(3,235,220);
	QColor* pColor = (&color);
	QColor** ppColor = &pColor;

	option.setPixelColor(color, 12, 4);
	option.setPixelColors(ppColor, 1, 1, 12, 4);

	return 0;
}
