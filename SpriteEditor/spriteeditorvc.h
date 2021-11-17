#ifndef SPRITEEDITORVC_H
#define SPRITEEDITORVC_H

#include <QMainWindow>
#include <QScrollArea>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QColorDialog>
#include <QMenuBar>
#include <QAction>
#include "spriteeditormodel.h"
#include <QTimer>
#include <QDir>
#include <QFileDialog>

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
	void updatePreview();
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
	int indexOfActiveFrame = 0;
	int indexOfPlayback = 0;
	int fps = 0;
	QTimer playbackUpdater;
	QString path = QDir::homePath();
	Ui::SpriteEditorVC *ui;
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
	SpriteEditorModel *model;

signals:
	void colorChanged(QColor color);
	void updateTool(SpriteEditorModel::ToolType toolType);
	void changeActiveColor(QPushButton*);
	void incrementToolSize();
	void decrementToolSize();
	void setActiveColor(QColor);
	void changeActiveFrame(int);
	void deleteFrame(int);
	void save(std::string, std::string);
	void load(std::string, std::string);
    void toggleGrid();
};
#endif // SPRITEEDITORVC_H
