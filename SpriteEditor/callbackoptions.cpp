#include "callbackoptions.h"

CallbackOptions::CallbackOptions(void (*_paintPixelColors)(Pointer2DArray<QColor> colors, unsigned int xCoord, unsigned int yCoord),
				void (*_setPixelColor)(QColor, unsigned int xCoord, unsigned int yCoord)) :
	paintPixelColors(_paintPixelColors), setPixelColor(_setPixelColor)
{ }
