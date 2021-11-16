#ifndef SPRITEEDITORMODEL_H
#define SPRITEEDITORMODEL_H
#include <QObject>
#include <QColor>
#include <QPainter>
#include <QImage>
#include <vector>
#include <string>
#include <QMap>
#include "itool.h"

using std::vector;
using std::string;

class SpriteEditorModel : public QObject{

Q_OBJECT

public:
	enum class ToolType {Pen, Brush, SoftEraser, HardEraser, ColorPicker};

private:
	int imageWidth;
	int imageHeight;
	int toolSize;
	QColor activeColor;
	QMap<ToolType, ITool*> Tools;
	ToolType activeTool;
	vector<QImage> frames;
	int activeFrameIndex;
	QPainter painter;

	void setColorOfActiveFrame(QColor, int xCoord, int yCoord);
	void setColorsOfActiveFrame(QColor[], int xCoord, int yCoord);
	void setPixelColors(Pointer2DArray<QColor> colors, unsigned int xCoord, unsigned int yCoord);

public:
	SpriteEditorModel(int imageWidth, int imageHeight) :imageWidth(imageWidth), imageHeight(imageHeight){};
	QImage getFramefromIndex(int index);
	int getFrameCount();

signals:
	void sendActiveFrame(int activeFrame);

public slots:
	void setActiveColor(QColor);
	void incrementBrushSize();
	void decrementBrushSize();
	void changeActiveFrame(int newFrameIndex);
	void deleteFrame(int indexOfFrameToDelete);
	void save(string filePath, string fileName);
	void load(string filePath, string fileName);
	void setActiveTool(ToolType newTool);
	void drawing(float x, float y);
};


#endif // SPRITEEDITORMODEL_H
