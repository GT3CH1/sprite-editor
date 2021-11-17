#ifndef SPRITEEDITORVC_H
#define SPRITEEDITORVC_H

#include <QAction>
#include <QColorDialog>
#include <QDir>
#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QPushButton>
#include <QScrollArea>
#include <QSlider>
#include <QTimer>

#include "renderarea.h"
#include "spriteeditormodel.h"
#include "ui_spriteeditorvc.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SpriteEditorVC; }
QT_END_NAMESPACE

class SpriteEditorVC : public QMainWindow
{
	Q_OBJECT

public:
	SpriteEditorVC(QWidget *parent = nullptr);
	~SpriteEditorVC();

public slots:
	void showColorDialog();
	void updateCustomButtonColors();
	void colorButtonClicked();
	void setInvertBrush();
	void setRainbowBrush();
	void setSoftEraser();
	void setHardPen();
	void setSoftBrush();
	void setHardEraser();

private slots:
	void sendActiveFrame();
	void deleteFrame();
	void addFrame();
	void previewFrames(vector<QPixmap>);
	void updateActivePreviewFrame(int);
	void updatePlaybackFrame();
	void on_fpsSlider_valueChanged(int);
	void keyPressEvent(QKeyEvent*);
	void savePressed();
	void loadPressed();
private:
	const char* FILE_FILTER = "Sprite Files (*.ssp);;All Files (*.*)";
	const int FPS_INTERVAL = 10;
	const int FPS_MAX = 60;
	const int FPS_STEP = 10;
	const int PREVIEW_SIZE = 128;
	SpriteEditorModel *model;
	Ui::SpriteEditorVC *ui;
	int indexOfActiveFrame = 0;
	int indexOfPlayback = 0;
	int fps = 0;
	QTimer playbackUpdater;
	QString path = QDir::homePath();
	void changeActiveColor(QPushButton*);
	std::vector<RenderArea*> framePreviews;
	QColorDialog *colorDialog;
	QAction *saveAction;
	QAction *openAction;
	QAction *closeAction;
	QAction *helpAction;
	QAction *newFileAction;

	QAction *rainbowBrushSelected;
	QAction *softEraserSelected;
	QAction *invertSelected;
	QAction *hardPenSelected;
	QAction *softBrushSelected;
	QAction *hardEraserSelected;

	QMenu *fileMenu;
	QMenu *helpMenu;
	QMenu *toolsMenu;
	void setButtonColor(QPushButton* button, QString hex);
	void createMenu();
	void setupButtonColors();
	constexpr unsigned int hash(const char* str, int h = 0);

signals:
	void colorChanged(QColor color);
	void updateTool(SpriteEditorModel::ToolType toolType);
	void incrementToolSize();
	void decrementToolSize();
	void setActiveColor(QColor);
	void changeActiveFrame(int);
	void changeActiveTool(SpriteEditorModel::ToolType);
	void add();
	void remove(int);
	void save(std::string, std::string);
	void load(std::string, std::string);
    void toggleGrid();
};
#endif // SPRITEEDITORVC_H
