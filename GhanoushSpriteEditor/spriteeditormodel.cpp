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
	QPixmap map(imageHeight, imageWidth);
	map.fill();
	frames.push_back(map);
	Tools.insert(ToolType::Brush, new PixelBrush(new SoftCircleStencilGenerator()));
	Tools.insert(ToolType::Pen, new PixelBrush(new SquareStencilGenerator()));
	Tools.insert(ToolType::HardEraser, new PixelEraser(new SquareStencilGenerator()));
	Tools.insert(ToolType::InvertBrush, new ColorInverterBrush(new SquareStencilGenerator()));
	Tools.insert(ToolType::Rainbow, new RainbowBrush(new SquareStencilGenerator()));
	Tools.insert(ToolType::SprayCan, new SprayCanBrush(new SoftCircleStencilGenerator()));
	Tools.insert(ToolType::SoftEraser, new PixelEraser(new SoftCircleStencilGenerator()));
	Tools.insert(ToolType::Gaussian, new GaussianBlurBrush(new SoftCircleStencilGenerator()));
	Tools.insert(ToolType::RainbowSprayCan, new RainBowSprayCanBrush(new SoftCircleStencilGenerator()));
	QPoint initialPosition(-1, -1);
	lastPosition = initialPosition;
}

SpriteEditorModel::~SpriteEditorModel()
{
	for (auto toolKeys : Tools)
		delete toolKeys;
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
	if (toolSize < imageHeight || toolSize < imageWidth)
		toolSize++;
	emit brushSizeChanged(toolSize);
}

/**
 * @brief SpriteEditorModel::decrementBrushSize
 */
void SpriteEditorModel::decrementBrushSize()
{
	if (toolSize > 1)
		toolSize--;
	emit brushSizeChanged(toolSize);
}

/**
 * @brief Sets the tool size to the given size.
 * @param size - The new tool size.
 */
void SpriteEditorModel::setToolSize(int size)
{
	toolSize = size;
	emit brushSizeChanged(toolSize);
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
	if (frames.size() == 1)
		frames[activeFrameIndex].fill();
	else
	{
		vector<QPixmap>::iterator itr = frames.begin();
		for (int i = 0; i < indexOfFrameToDelete; i++)
			itr++;
		frames.erase(itr);
		if (activeFrameIndex > 0)
			activeFrameIndex--;
	}
	emit sendActiveFrameIndex(activeFrameIndex);
	emit sendFrames(frames);
}

/**
 * @brief Adds a new frame to the sprite editor.
 */
void SpriteEditorModel::addFrame()
{
	activeFrameIndex++;
	QPixmap blank(imageHeight, imageHeight);
	blank.fill();
	if ((uint)activeFrameIndex == frames.size())
		frames.push_back(blank);
	else
	{
		QPixmap temp = frames[activeFrameIndex];
		frames[activeFrameIndex] = blank;
		for (unsigned int j = activeFrameIndex + 1; j < frames.size(); j++)
			swap(temp, frames[j]);
		frames.push_back(temp);
	}
	emit sendActiveFrameIndex(activeFrameIndex);
	emit sendFrames(frames);
}

/**
 * @brief Duplicates a frame to the sprite editor.
 */
void SpriteEditorModel::duplicateFrame()
{
	QPixmap copy = frames[activeFrameIndex];
	activeFrameIndex++;
	if ((uint)activeFrameIndex == frames.size())
		frames.push_back(copy);
	else
	{
		QPixmap temp = frames[activeFrameIndex];
		frames[activeFrameIndex] = copy;
		for (unsigned int j = activeFrameIndex + 1; j < frames.size(); j++)
			swap(temp, frames[j]);
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
	// create the file
	QString saveFileName = QString::fromStdString(filePath + fileName);
	QFile saveFile(saveFileName);
	// write the file
	if (saveFile.open(QIODevice::WriteOnly))
	{
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
	json["frames"] = QJsonObject();
	QJsonObject frames(json["frames"].toObject());
	for (int i = 0; i < frameCount; i++)
		writeFrame(frames, i);
	json["frames"] = frames;
}

/**
 * @brief SpriteEditorModel::writeFrame
 * @param json
 * @param frameNumber
 */
void SpriteEditorModel::writeFrame(QJsonObject &json, int frameNumber) const
{
	QString currFrame = QString("frame%1").arg(frameNumber);
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
	QColor pixelColor = frame.pixelColor(row, col);
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
	// load the file
	QString loadFileName = QString::fromStdString(filePath + fileName + ".ssp");
	QFile loadFile(loadFileName);
	// read the file
	if (loadFile.open(QIODevice::ReadOnly))
	{
		QByteArray saveData = loadFile.readAll();
		QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
		frames.clear();
		read(loadDoc.object());
	}
	emit sendActiveFrameIndex(0);
	emit sendFrames(frames);
	emit sendActiveFrame(frames[0]);
	emit updateCanvasSize(imageHeight);
}

/**
 * @brief SpriteEditorModel::read
 * @param json
 */
void SpriteEditorModel::read(const QJsonObject &json)
{
	if (json.contains("height") && json["height"].isDouble())
		imageHeight = json["height"].toInt();
	if (json.contains("width") && json["width"].isDouble())
		imageWidth = json["width"].toInt();
	int size = 0;
	if (json.contains("numberOfFrames") && json["numberOfFrames"].isDouble())
		size = json["numberOfFrames"].toInt();
	for (int i = 0; i < size; i++)
	{
		QString frameName = QString("frame%1");
		frameName = frameName.arg(i);
		char *c = strcpy(new char[frameName.length() + 1], frameName.toStdString().c_str());
		readFrame(json["frames"][c].toArray(), i);
	}
}

/**
 * @brief SpriteEditorModel::readFrame
 * @param json
 * @param frameNumber
 */
void SpriteEditorModel::readFrame(const QJsonValue &json, int frameNumber)
{
	QJsonArray frameRow = json[frameNumber].toArray();
	QImage newFrame(imageWidth, imageHeight, QImage::Format_RGBA8888);
	for (int j = 0; j < frameRow.size(); j++)
		readRow(json.toArray(), newFrame, j);
	QPixmap frame(QPixmap::fromImage(newFrame));
	frames.push_back(frame);
}

/**
 * @brief SpriteEditorModel::readRow
 * @param json
 * @param currFrame
 * @param newFrame
 * @param x
 */
void SpriteEditorModel::readRow(const QJsonArray &json, QImage &newFrame, int row)
{
	QJsonArray rows(json[row].toArray());
	for (int i = 0; i < rows.size(); i++)
	{
		QJsonArray currentPixel(rows[i].toArray());
		QColor color(currentPixel[0].toInt(), currentPixel[1].toInt(), currentPixel[2].toInt(), currentPixel[3].toInt());
		newFrame.setPixelColor(row, i, color);
	}
}

/**
 * @brief Reads a color from a QJsonArray, and sets the color of a pixel at the row and col on the QImage.
 * @param pixel - A QJsonArray containing a list of colors
 * @param row - The row to draw at.
 * @param col - Te column to draw at.
 * @param newFrame - The QImage to draw on.
 */
void SpriteEditorModel::readColor(QJsonArray pixel, int row, int col, QImage &newFrame)
{
	QColor color(pixel[0].toInt(), pixel[1].toInt(), pixel[2].toInt(), pixel[3].toInt());
	newFrame.setPixelColor(row, col, color);
}

/**
 * @brief Sets the active tool to the given tool/
 * @param newTool - new active tool
 */
void SpriteEditorModel::setActiveTool(ToolType newTool)
{
	activeTool = newTool;
}

/**
 * @brief Sets the colors of the active frame to the given 2d array and the X and Y coordinates.
 * @param newColors - A Pointer2DArray containing all of the new colors.
 * @param xCoord - The X coordinate to draw at.
 * @param yCoord - The Y coordinate to draw at.
 */
void SpriteEditorModel::setColorsOfActiveFrame(Pointer2DArray<QColor> newColors, unsigned int xCoord, unsigned int yCoord)
{
	QPainter painter(&frames[activeFrameIndex]);
	for (unsigned int i = 0; i < newColors.getWidth(); i++)
	{
		for (unsigned int j = 0; j < newColors.getHeight(); j++)
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

/**
 * @brief Replaces the pixels of the area defined by newColors and xCoord and yCoord
 * with the colors in newColors.
 * @param newColors - The colors of the pixels to be set to.
 * @param xCoord - The x coordinate of the upper left corner of the area to replace.
 * @param yCoord - The y coordinate of the upper left corner of the area to replace.
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
	int currentX = (int)(x * imageWidth);
	int currentY = (int)(y * imageHeight);
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
 * @param x - The x coordinate of the mouse.
 * @param y - The y coordinate of the mouse.
 */
void SpriteEditorModel::stopDrawing()
{
	newStroke = true;
	QPoint initialPosition(-1, -1);
	lastPosition = initialPosition;
}


/**
 * @brief Sets the frame list to the given vector.
 * @param map - The list of new frames.
 */
void SpriteEditorModel::setFrames(std::vector<QPixmap> map)
{
	frames = map;
}

/**
 * @brief Sets the size of the image and updates the canvas.
 * @param width - The width of the image.
 * @param height - The height of the image.
 */
void SpriteEditorModel::setSize(int width, int height)
{
	imageWidth = width;
	imageHeight = height;
	activeFrameIndex = 0;
	QPixmap firstFrame(width, height);
	firstFrame.fill();
	frames.clear();
	frames.push_back(firstFrame);
	emit sendActiveFrameIndex(0);
	emit sendFrames(frames);
	emit sendActiveFrame(firstFrame);
	emit updateCanvasSize(imageHeight);
}

void SpriteEditorModel::clearFrame()
{
	frames[activeFrameIndex].fill();
	emit sendActiveFrame(frames[activeFrameIndex]);
	emit sendActiveFrameIndex(activeFrameIndex);
}
