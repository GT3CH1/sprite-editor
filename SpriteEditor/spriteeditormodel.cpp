/* Alex Richins 11/10/21
 * spriteeditormodel handles tools and the sprite itself as well as all modifications of the sprite
 */
#include "spriteeditormodel.h"
/**
 * @brief SpriteEditorModel::getFramefromIndex
 * @param index, frame index within vector
 * @return QImage for that frame
 */
QImage SpriteEditorModel::getFramefromIndex(int index)
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
	// TODO(ALEX): need to work with kenzie and william once tools are more done
}

/**
 * @brief SpriteEditorModel::decrementBrushSize
 */
void SpriteEditorModel::decrementBrushSize()
{
	// TODO(ALEX): need to work with kenzie and william once tools are more done
}

/**
 * @brief SpriteEditorModel::changeActiveFrame
 * @param newFrameIndex, new active frame index
 */
void SpriteEditorModel::changeActiveFrame(int newFrameIndex)
{
	activeFrameIndex = newFrameIndex;
	emit sendActiveFrame(activeFrameIndex);
}

/**
 * @brief SpriteEditorModel::deleteFrame
 * @param indexOfFrameToDelete
 */
void SpriteEditorModel::deleteFrame(int indexOfFrameToDelete)
{
	vector<QImage>::iterator itr = frames.begin();
	for(int i = 0; i <= indexOfFrameToDelete; i++)
		itr++;
	frames.erase(itr);
	if(activeFrameIndex > 0)
		activeFrameIndex--;
	emit sendActiveFrame(activeFrameIndex);
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
void SpriteEditorModel::setColorOfActiveFrame(QColor newColor, int xCoord, int yCoord)
{
	//TODO(ALEX): talk to william and kenzie more about tool interaction
}

/**
 * @brief SpriteEditorModel::setColorsOfActiveFrame
 * @param newColors
 * @param xCoord
 * @param yCoord
 */
void SpriteEditorModel::setColorsOfActiveFrame(QColor newColors[], int xCoord, int yCoord)
{
	//TODO(ALEX): talk to william and kenzie more about tool interaction
}
