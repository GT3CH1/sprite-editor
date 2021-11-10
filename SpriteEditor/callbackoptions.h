#ifndef CALLBACKOPTIONS_H
#define CALLBACKOPTIONS_H

#include <QColor>

struct CallbackOptions
{
public:
	CallbackOptions(void (*_setPixelColors)(QColor**, unsigned int xCoord, unsigned int yCoord),
					void (*_setPixelColor)(QColor, unsigned int xCoord, unsigned int yCoord));
	//https://stackoverflow.com/questions/10003270/gcc-array-type-has-incomplete-element-type
	void (*setPixelColors)(QColor**, unsigned int xCoord, unsigned int yCoord);
	void (*setPixelColor)(QColor, unsigned int xCoord, unsigned int yCoord);
};

#endif // CALLBACKOPTIONS_H
