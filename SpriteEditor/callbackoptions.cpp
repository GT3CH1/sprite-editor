#include "callbackoptions.h"

CallbackOptions::CallbackOptions(void (*_setPixelColors)(Pointer2DArray<QColor> colors, unsigned int xCoord, unsigned int yCoord),
				void (*_setPixelColor)(QColor, unsigned int xCoord, unsigned int yCoord)) :
	setPixelColors(_setPixelColors), setPixelColor(_setPixelColor)
{ }
