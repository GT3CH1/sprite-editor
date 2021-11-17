/* Alex Richins 11/10/21
 * spriteeditormodel handles tools and the sprite itself as well as all modifications of the sprite
 */
#include <functional>
#include "spriteeditormodel.h"
#include "actionstate.h"
#include "itool.h"
#include "pointer2darray.h"
#include <QDebug>
#include <pixelbrush.h>
#include <squarestencilgenerator.h>
#include <softcirclestencilgenerator.h>
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
	emit sendActiveFrame(map);
	frames.push_back(map);
	ITool* tool = new PixelBrush(new SoftCircleStencilGenerator());
	Tools.insert(ToolType::Brush,tool);
	Tools.insert(ToolType::Pen,new PixelBrush(new SquareStencilGenerator()));
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
	qDebug() << "Tool size is now" << toolSize;
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
	vector<QPixmap>::iterator itr = frames.begin();
	for(int i = 0; i <= indexOfFrameToDelete; i++)
		itr++;
	frames.erase(itr);
	if(activeFrameIndex > 0)
		activeFrameIndex--;
	emit sendActiveFrameIndex(activeFrameIndex);
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
 * @brief SpriteEditorModel::setColorOfActiveFrame
 * @param newColor
 * @param xCoord
 * @param yCoord
 */
void SpriteEditorModel::setColorOfActiveFrame(QColor newColor, unsigned int xCoord, unsigned int yCoord)
{
	emit sendActiveFrame(frames[activeFrameIndex]);
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
	qDebug() << "Active Tool: " <<activeTool;
	painter.end();
	emit sendActiveFrame(frames[activeFrameIndex]);
}



/**
 * @brief SpriteEditorModel::drawing
 * @param x 0-1 for mouse position on drawing grid
 * @param y 0-1 for mouse position on drawing grid
 */
void SpriteEditorModel::drawing(float x, float y){
	qDebug() << "Received click: " <<x << " " << y;
	ActionState toolActionState(toolSize, activeColor, (int)(x*imageWidth), (int)(y*imageHeight), frames[activeFrameIndex]);
	std::function<void(Pointer2DArray<QColor>, unsigned int, unsigned int)> setPixelColorsCallback = [&](Pointer2DArray<QColor> colors, unsigned int xCoord, unsigned int yCoord) {this->setColorsOfActiveFrame(colors, xCoord, yCoord); };
	CallbackOptions callBack(setPixelColorsCallback);
	Tools[activeTool]->apply(toolActionState, callBack);
}

