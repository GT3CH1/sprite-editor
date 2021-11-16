#ifndef SPRITEEDITORVC_H
#define SPRITEEDITORVC_H

#include <QMainWindow>
#include <QScrollArea>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QTimer>
#include <QDir>
#include <QFileDialog>

#include "spriteeditormodel.h"
#include "renderarea.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SpriteEditorVC; }
QT_END_NAMESPACE

class SpriteEditorVC : public QMainWindow
{
	Q_OBJECT

public:
    // TODO(gcpease): Add all the buttons for tools
    QPushButton *tool1;

	SpriteEditorVC(QWidget *parent = nullptr);
	~SpriteEditorVC();

private slots:
	void updatePreview();
	void on_fpsSlider_valueChanged(int);
	void keyPressEvent(QKeyEvent*);
	void savePressed();
	void loadPressed();
	void on_primaryColorButton1_clicked();
	void on_primaryColorButton2_clicked();
	void on_primaryColorButton3_clicked();
	void on_primaryColorButton4_clicked();
	void on_primaryColorButton5_clicked();
	void on_primaryColorButton6_clicked();
	void on_primaryColorButton7_clicked();
	void on_primaryColorButton8_clicked();
	void on_customColorButton1_clicked();
	void on_customColorButton2_clicked();
	void on_customColorButton3_clicked();
	void on_customColorButton4_clicked();
	void on_customColorButton5_clicked();
	void on_customColorButton6_clicked();
	void on_customColorButton7_clicked();
	void on_customColorButton8_clicked();
	void on_penToolButton_clicked();
	void on_brushToolButton_clicked();
	void on_eraserToolButton_clicked();
	void on_toolButton4_clicked();

private:
	const char* FILE_FILTER = "Sprite Files (*.ssp);;All Files (*.*)";
	const int FPS_INTERVAL = 10;
	const int FPS_MAX = 60;
	const int FPS_STEP = 10;
	SpriteEditorModel *model;
	Ui::SpriteEditorVC *ui;
	int indexOfActiveFrame = 0;
	int indexOfPlayback = 0;
	int fps = 0;
	QTimer playbackUpdater;
	QString path = QDir::homePath();
	void changeActiveColor(QPushButton*);
	std::vector<RenderArea> framePreviews;

signals:
	void incrementToolSize();
	void decrementToolSize();
	void setActiveColor(QColor);
	void changeActiveFrame(int);
	void changeActiveTool(SpriteEditorModel::ToolType);
	void deleteFrame(int);
	void save(std::string, std::string);
	void load(std::string, std::string);
};
#endif // SPRITEEDITORVC_H
