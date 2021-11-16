#include <functional>
#include "callbackoptions.h"
CallbackOptions::CallbackOptions(std::function<void(Pointer2DArray<QColor>, unsigned int, unsigned int)> setPixelColorsFunc)
{
	setPixelColors = setPixelColorsFunc;
}
