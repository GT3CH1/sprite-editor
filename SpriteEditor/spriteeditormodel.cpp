/* Alex Richins 11/10/21
 * spriteeditormodel handles tools and the sprite itself as well as all modifications of the sprite
 */
#include <functional>
#include "spriteeditormodel.h"
#include "actionstate.h"
#include "itool.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>

/**
 * @brief SpriteEditorModel::SpriteEditorModel
 */
SpriteEditorModel::SpriteEditorModel()
{
	imageHeight = 64;
	imageWidth = 64;
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
	toolSize++;
}

/**
 * @brief SpriteEditorModel::decrementBrushSize
 */
void SpriteEditorModel::decrementBrushSize()
{
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
	// create the file
	QString saveFileName = QString::fromStdString(filePath + "/" + fileName + ".ssp");
	QFile saveFile(saveFileName);

	// write the file
	if (saveFile.open(QIODevice::WriteOnly)) {
		QJsonObject save;
		write(save);
		saveFile.write(QJsonDocument(save).toJson());
	}
}

/**
 * @brief SpriteEditorModel::write
 * @param json
 */
void SpriteEditorModel::write(QJsonObject &json) const
{
	json["height"] = imageHeight;
	json["width"] = imageWidth;
	int frameCount = frames.size();
	json["numberOfFrames"] = frameCount;

	for (int i = 0; i < frameCount; i++)
		writeFrame(json, i);

}

/**
 * @brief SpriteEditorModel::writeFrame
 * @param json
 * @param frameNumber
 */
void SpriteEditorModel::writeFrame(QJsonObject& json, int frameNumber) const
{
	QString currFrame = QString::fromStdString("frame" + std::to_string(frameNumber));
	QImage frame = frames[frameNumber].toImage();

	QJsonArray pixels;

	for (int i = 0; i < imageWidth; i++)
		pixels.append(writeRows(frame, i));

	json.insert(currFrame, pixels);
}

/**
 * @brief SpriteEditorModel::writeRows
 * @param frame
 * @param row
 * @return
 */
QJsonArray SpriteEditorModel::writeRows(QImage frame, int row) const
{
	QJsonArray rows;

	for (int i = 0; i < imageHeight; i++)
		rows.append(writeColor(frame, row, i));

	return rows;

}

/**
 * @brief SpriteEditorModel::writeColor
 * @param frame
 * @param row
 * @param col
 * @return
 */
QJsonArray SpriteEditorModel::writeColor(QImage frame, int row, int col) const
{
	QJsonArray colors;

	QColor pixelColor = frame.pixelColor(row,col);
	colors.append(pixelColor.red());
	colors.append(pixelColor.green());
	colors.append(pixelColor.blue());
	colors.append(pixelColor.alpha());
	return colors;
}

/**
 * @brief SpriteEditorModel::load
 * @param filePath, file path to location to be save at
 * @param fileName, save file name
 */
void SpriteEditorModel::load(string filePath, string fileName)
{
	//TODO(ALEX): talk to gavin about json and stufffffff

	// open the file!

	QJsonObject load;
	write(load);



}

/**
 * @brief SpriteEditorModel::load
 * @param json
 */
void SpriteEditorModel::read(const QJsonObject &json)
{
	if (json.contains("height") && json["height"].isDouble())
		imageHeight = json["height"].toInt();

	if (json.contains("width") && json["width"].isDouble())
		imageWidth = json["width"].toInt();

	if (json.contains("numberOfFrames") && json["numberofFrames"].isDouble())
	{
		int size = json["numberOfFrames"].toInt();
		frames.resize(size);
	}

	int size = frames.size();
	for (int i = 0; i < size; i++)
		readFrame(json, i);
}

/**
 * @brief SpriteEditorModel::readFrame
 * @param json
 * @param frameNumber
 */
void SpriteEditorModel::readFrame(const QJsonObject &json, int frameNumber)
{
	QString currFrame = QString::fromStdString("frame" + std::to_string(frameNumber));
	if (json.contains(currFrame) && json[currFrame].isArray())
	{
		QJsonArray frameArray = json[currFrame].toArray();
		QImage newFrame;

		for (int j = 0; j < frameArray.size(); j++)
			readRow(json, currFrame, newFrame, j);

		QPixmap frame;
		frame.fromImage(newFrame);
		frames.assign(frameNumber, frame);

	}

}

/**
 * @brief SpriteEditorModel::readRow
 * @param json
 * @param currFrame
 * @param newFrame
 * @param x
 */
void SpriteEditorModel::readRow(const QJsonObject &json, QString currFrame, QImage newFrame, int x)
{
	QJsonArray pixels = json.value(currFrame).toArray();

	for (int i = 0; i < pixels.size(); i++)
	{
		QJsonArray currPixel = pixels[i].toArray();
		QColor newColor(currPixel[0].toInt(), currPixel[1].toInt(), currPixel[2].toInt(), currPixel[3].toInt());
		newFrame.setPixelColor(x, i, newColor);
	}
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
	QPainter painter(&frames[activeFrameIndex]);
	painter.fillRect(xCoord, yCoord, 1, 1, newColor);
	painter.end();
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
	painter.end();
	emit sendActiveFrame(frames[activeFrameIndex]);
}



/**
 * @brief SpriteEditorModel::drawing
 * @param x 0-1 for mouse position on drawing grid
 * @param y 0-1 for mouse position on drawing grid
 */
void SpriteEditorModel::drawing(float x, float y){
	ActionState toolActionState(toolSize, activeColor, (int)(x*imageWidth), (int)(y*imageHeight), frames[activeFrameIndex]);
	std::function<void(Pointer2DArray<QColor>, unsigned int, unsigned int)> setPixelColorsCallback = [&](Pointer2DArray<QColor> colors, unsigned int xCoord, unsigned int yCoord) {this->setColorsOfActiveFrame(colors, xCoord, yCoord); };
	CallbackOptions callBack(setPixelColorsCallback);
	Tools[activeTool]->apply(toolActionState, callBack);
}

