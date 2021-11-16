#ifndef SPRITEEDITORMODEL_H
#define SPRITEEDITORMODEL_H
#include <QObject>
#include <QColor>
#include <QPainter>
#include <QImage>
#include <vector>
#include <string>
// #include "itool.h" Waiting for itool.h from TODO(kenzie and william):

using std::vector;
using std::string;

class SpriteEditorModel : public QObject{

Q_OBJECT

public:
	enum ToolType {Pen, Brush, SoftEraser, HardEraser, ColorPicker};
	SpriteEditorModel() = default;
private:
	int imageWidth;
	int imageHeight;
	int toolSize;
	QColor activeColor;
	// map<ToolType, iTool> Tools; Waiting for itool.h from TODO(kenzie and william):
	ToolType activeTool;
	vector<QImage> frames;
	int activeFrameIndex;
	QPainter painter;

	void setColorOfActiveFrame(QColor, int xCoord, int yCoord);
	void setColorsOfActiveFrame(QColor[], int xCoord, int yCoord);

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
};


#endif // SPRITEEDITORMODEL_H
