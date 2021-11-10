/* Alex Richins 11/10/21
 * spriteeditormodel handles tools and the sprite itself as well as all modifications of the sprite
 */
#include "spriteeditormodel.h"

QImage SpriteEditorModel::getFramefromIndex(int index)
{
	return frames[index];
}
int SpriteEditorModel::getFrameCount()
{
	return frames.size();
}

void SpriteEditorModel::setActiveColor(QColor newColor)
{
	activeColor = newColor;
	// TODO(ALEX): see what else needs to be done
}
void SpriteEditorModel::incrementBrushSize()
{
	// TODO(ALEX): need to work with kenzie and william once tools are more done
}
void SpriteEditorModel::decrementBrushSize()
{
	// TODO(ALEX): need to work with kenzie and william once tools are more done
}
void SpriteEditorModel::changeActiveFrame(int newFrameIndex)
{
	activeFrameIndex = newFrameIndex;
	// TODO(ALEX): update new frame
}
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
void SpriteEditorModel::save(string filePath, string fileName)
{
	//TODO(ALEX): talk to gavin about json and stufffffff
}
void SpriteEditorModel::load(string filePath, string fileName)
{
	//TODO(ALEX): talk to gavin about json and stufffffff
}
void SpriteEditorModel::setActiveTool(ToolType newTool)
{
	activeTool = newTool;
}

void SpriteEditorModel::setColorOfActiveFrame(QColor, int xCoord, int yCoord)
{
	//TODO(ALEX): talk to william and kenzie more about tool interaction
}
void SpriteEditorModel::setColorsOfActiveFrame(QColor[], int xCoord, int yCoord)
{
	//TODO(ALEX): talk to william and kenzie more about tool interaction
}
