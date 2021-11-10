#include "callbackoptions.h"

CallbackOptions::CallbackOptions(void (*_setPixelColors)(QColor**, unsigned int width, unsigned int height, unsigned int xCoord, unsigned int yCoord),
				void (*_setPixelColor)(QColor, unsigned int xCoord, unsigned int yCoord)) :
	setPixelColors(_setPixelColors), setPixelColor(_setPixelColor)
{ }
