#include <functional>
#include "callbackoptions.h"
CallbackOptions::CallbackOptions(std::function<void(Pointer2DArray<QColor>, unsigned int, unsigned int)> paintPixelColorsFunc,
								 std::function<void(Pointer2DArray<QColor>, unsigned int, unsigned int)> replacePixelColorsFunc)
{
	paintPixelColors = paintPixelColorsFunc;
	replacePixelColors = replacePixelColorsFunc;
}
