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
	int toolSize = 1;
	QColor activeColor = Qt::blue;
	QMap<ToolType, ITool*> Tools;
	ToolType activeTool = ToolType::Pen;
	vector<QPixmap> frames;
	int activeFrameIndex =0;

	void setColorOfActiveFrame(QColor, unsigned int, unsigned int);
	void setColorsOfActiveFrame(Pointer2DArray<QColor>, unsigned int, unsigned int);
	void write(QJsonObject& json) const;
	void writeFrame(QJsonObject& json, int frameNumber) const;
	QJsonArray writeRows(QImage frame, int row) const;
	QJsonArray writeColor(QImage frame, int row, int col) const;
	void read(const QJsonObject& json);
	void readFrame(const QJsonObject &json, int frameNumber);
	void readRow(const QJsonObject &json, QString currFrame, QImage newFrame, int row);
	void readColor(QJsonArray newColor, int row, int col, QImage newFrame);
	void replaceColorsOfActiveFrame(Pointer2DArray<QColor> newColors, unsigned int xCoord, unsigned int yCoord);

public:
	SpriteEditorModel(int imageWidth, int imageHeight) :imageWidth(imageWidth), imageHeight(imageHeight){};
	SpriteEditorModel();
	~SpriteEditorModel();
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
	void addFrame();
	void duplicateFrame();
	void save(string filePath, string fileName);
	void load(string filePath, string fileName);
	void setActiveTool(ToolType newTool);
	void drawing(float x, float y);
};


#endif // SPRITEEDITORMODEL_H
