/* Alex Richins 11/10/21
 * spriteeditormodel handles tools and the sprite itself as well as all modifications of the sprite
 */
#include <functional>
#include <stencils.h>
#include <brushes.h>
#include <spriteeditormodel.h>
#include <actionstate.h>
#include <itool.h>
#include <pointer2darray.h>

#include <brush.h>
#include <stencil.h>

/**
 * @brief SpriteEditorModel::SpriteEditorModel
 */
SpriteEditorModel::SpriteEditorModel()
{
	imageHeight = 64;
	imageWidth = 64;
	toolSize = 4;
	QPixmap map(imageHeight,imageWidth);
	map.fill();
	frames.push_back(map);
	Tools.insert(ToolType::Brush,new PixelBrush(new SoftCircleStencilGenerator()));
	Tools.insert(ToolType::Pen,new PixelBrush(new SquareStencilGenerator()));
	Tools.insert(ToolType::HardEraser,new PixelEraser(new SquareStencilGenerator()));
	Tools.insert(ToolType::InvertBrush,new ColorInverterBrush(new SquareStencilGenerator()));
	Tools.insert(ToolType::Rainbow,new RainbowBrush(new SquareStencilGenerator()));
	Tools.insert(ToolType::SprayCan,new SprayCanBrush(new SoftCircleStencilGenerator()));
	Tools.insert(ToolType::SoftEraser,new PixelEraser(new SoftCircleStencilGenerator()));
	QPoint initialPosition(-1,-1);
	lastPosition = initialPosition;
}

SpriteEditorModel::~SpriteEditorModel()
{
	for(auto toolKeys : Tools.keys())
		delete Tools.value(toolKeys);
}

/**
 * @brief SpriteEditorModel::getFramefromIndex
 * @param index, frame index within vector
 * @return QImage for that frame
 */
QPixmap SpriteEditorModel::getFramefromIndex(int index)
{
	return frames[index];
}

/**
 * @brief SpriteEditorModel::getFrameCount
 * @return int, number of frames
 */
int SpriteEditorModel::getFrameCount()
{
	return frames.size();
}

/**
 * @brief SpriteEditorModel::setActiveColor
 * @param newColor, new active color
 */
void SpriteEditorModel::setActiveColor(QColor newColor)
{
	activeColor = newColor;
	// TODO(ALEX): see what else needs to be done
}

/**
 * @brief SpriteEditorModel::incrementBrushSize
 */
void SpriteEditorModel::incrementBrushSize()
{
	if(toolSize < imageHeight || toolSize < imageWidth)
		toolSize++;
}

/**
 * @brief SpriteEditorModel::decrementBrushSize
 */
void SpriteEditorModel::decrementBrushSize()
{
	if(toolSize > 1)
		toolSize--;
}

/**
 * @brief SpriteEditorModel::changeActiveFrame
 * @param newFrameIndex, new active frame index
 */
void SpriteEditorModel::changeActiveFrame(int newFrameIndex)
{
	activeFrameIndex = newFrameIndex;
	emit sendActiveFrameIndex(activeFrameIndex);
}

/**
 * @brief SpriteEditorModel::deleteFrame
 * @param indexOfFrameToDelete
 */
void SpriteEditorModel::deleteFrame(int indexOfFrameToDelete)
{
	if(frames.size() == 1)
	{
		frames[activeFrameIndex].fill();
	}else{
	vector<QPixmap>::iterator itr = frames.begin();
	for(int i = 0; i <= indexOfFrameToDelete; i++)
		itr++;
	frames.erase(itr);
	if(activeFrameIndex > 0)
		activeFrameIndex--;	
	}
	emit sendActiveFrameIndex(activeFrameIndex);
	emit sendFrames(frames);
}

/**
 * @brief SpriteEditorModel::addFrame
 */
void SpriteEditorModel::addFrame()
{
	activeFrameIndex++;
	QPixmap blank(imageHeight,imageHeight);
	blank.fill();
	if(activeFrameIndex == frames.size())
	{
		frames.push_back(blank);

	}else{
	QPixmap temp = frames[activeFrameIndex];
	frames[activeFrameIndex] = blank;
	for(unsigned int j = activeFrameIndex + 1; j < frames.size(); j++)
	{
		swap(temp, frames[j]);
	}
	frames.push_back(temp);
	}
	emit sendActiveFrameIndex(activeFrameIndex);
	emit sendFrames(frames);
}
/**
 * @brief SpriteEditorModel::duplicateFrame
 */
void SpriteEditorModel::duplicateFrame()
{

	QPixmap copy = frames[activeFrameIndex];
	activeFrameIndex++;
	if(activeFrameIndex == frames.size())
	{
		frames.push_back(copy);
	}else{
	QPixmap temp = frames[activeFrameIndex];
	frames[activeFrameIndex] = copy;
	for(unsigned int j = activeFrameIndex + 1; j < frames.size(); j++)
	{
		swap(temp, frames[j]);
	}
	frames.push_back(temp);
	}
	emit sendActiveFrameIndex(activeFrameIndex);
	emit sendFrames(frames);
}

/**
 * @brief SpriteEditorModel::save
 * @param filePath, file path to location to be save at
 * @param fileName, save file name
 */
void SpriteEditorModel::save(string filePath, string fileName)
{
	//TODO(ALEX): talk to gavin about json and stufffffff
}

/**
 * @brief SpriteEditorModel::load
 * @param filePath, file path to location to be save at
 * @param fileName, save file name
 */
void SpriteEditorModel::load(string filePath, string fileName)
{
	//TODO(ALEX): talk to gavin about json and stufffffff
}

/**
 * @brief SpriteEditorModel::setActiveTool
 * @param newTool, new active tool
 */
void SpriteEditorModel::setActiveTool(ToolType newTool)
{
	activeTool = newTool;
	//TODO(ALEX): don't think i need to do more, but we see
}

/**
 * @brief SpriteEditorModel::setColorsOfActiveFrame
 * @param newColors
 * @param xCoord
 * @param yCoord
 */
void SpriteEditorModel::setColorsOfActiveFrame(Pointer2DArray<QColor> newColors, unsigned int xCoord, unsigned int yCoord)
{
	QPainter painter(&frames[activeFrameIndex]);
	for(unsigned int i = 0; i < newColors.getWidth(); i++)
	{
		for(unsigned int j = 0; j < newColors.getHeight(); j++)
		{
			QColor pixelColor = newColors[i][j];
			int xPixel = xCoord + i;
			int yPixel = yCoord + j;
			painter.fillRect(xPixel, yPixel, 1, 1, pixelColor);
		}
	}
	painter.end();
	emit sendActiveFrame(frames[activeFrameIndex]);
	emit sendActiveFrameIndex(activeFrameIndex);
}

/** William Erignac
 *
 * @brief Replaces the pixels of the area defined by newColors and xCoord and yCoord
 * with the colors in newColors.
 * @param newColors The colors of the pixels to be set to.
 * @param xCoord The x coordinate of the upper left corner of the area to replace.
 * @param yCoord The y coordinate of the upper left corner of the area to replace.
 */
void SpriteEditorModel::replaceColorsOfActiveFrame(Pointer2DArray<QColor> newColors, unsigned int xCoord, unsigned int yCoord)
{
	QPainter clearer(&frames[activeFrameIndex]);
	clearer.eraseRect(xCoord, yCoord, newColors.getWidth(), newColors.getHeight());
	clearer.end();
	setColorsOfActiveFrame(newColors, xCoord, yCoord);
}

/**
 * @brief Draws on the main canvas
 * @param x - 0-1 for mouse position on drawing grid
 * @param y - 0-1 for mouse position on drawing grid
 */
void SpriteEditorModel::drawing(float x, float y)
{
	int currentX = (int)(x*imageWidth);
	int currentY = (int)(y*imageHeight);

	QPoint currentPosition(currentX, currentY);

	if (currentX != lastPosition.x() || currentY != lastPosition.y())
	{
		ActionState toolActionState(toolSize, activeColor, currentX, currentY, newStroke, frames[activeFrameIndex]);
		if (newStroke)
			newStroke = false;

		std::function<void(Pointer2DArray<QColor>, unsigned int, unsigned int)> paintPixelColorsCallback = [&](Pointer2DArray<QColor> colors, unsigned int xCoord, unsigned int yCoord)
		{
			this->setColorsOfActiveFrame(colors, xCoord, yCoord);
		};
		std::function<void(Pointer2DArray<QColor>, unsigned int, unsigned int)> replacePixelColorsCallback = [&](Pointer2DArray<QColor> colors, unsigned int xCoord, unsigned int yCoord)
		{
			this->replaceColorsOfActiveFrame(colors, xCoord, yCoord);
		};
		CallbackOptions callBack(paintPixelColorsCallback, replacePixelColorsCallback);
		Tools[activeTool]->apply(toolActionState, callBack);
		lastPosition = currentPosition;
	}
}

/**
 * @brief Informs the model that a stroke has ended.
 * @param x The x coordinate of the mouse.
 * @param y The y coordinate of the mouse.
 */
void SpriteEditorModel::stopDrawing(float x, float y)
{
	newStroke = true;
	QPoint initialPosition(-1,-1);
	lastPosition = initialPosition;
}

