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
	enum ToolType {Pen, Brush, SoftEraser, HardEraser, ColorPicker};

private:
	int imageWidth;
	int imageHeight;
	int toolSize;
	QColor activeColor;
	QMap<ToolType, ITool*> Tools;
	ToolType activeTool;
	vector<QPixmap> frames;
	int activeFrameIndex;
	QPainter painter;

	void setColorOfActiveFrame(QColor, unsigned int, unsigned int);
	void setColorsOfActiveFrame(Pointer2DArray<QColor>, unsigned int, unsigned int);

public:
	SpriteEditorModel(int imageWidth, int imageHeight) :imageWidth(imageWidth), imageHeight(imageHeight){};
	SpriteEditorModel();
	QPixmap getFramefromIndex(int index);
	int getFrameCount();

signals:
	void sendActiveFrame(QPixmap activeFrame);
	void sendActiveFrameIndex(int activeFrameIndex);
	void sendFrames(vector<QPixmap> allFrames);

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
