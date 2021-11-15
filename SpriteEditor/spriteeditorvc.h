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
    void on_fpsSlider_valueChanged(int value);
	void keyPressEvent(QKeyEvent*);
	void savePressed();
	void loadPressed();

private:
	const char* FILE_FILTER = "Sprite Files (*.ssp);;All Files (*.*)";
	Ui::SpriteEditorVC *ui;
	int indexOfActiveFrame;
	int indexOfPlayback;
	int fps = 0;
	QTimer playbackUpdater;
	QString path = QDir::homePath();

signals:
	void switchActiveFrame(int);
	void incrementToolSize();
	void decrementToolSize();
	void setActiveColor(QColor);
	void incrementBrushSize();
	void decrementBrushSize();
	void changeActiveFrame(int);
	void deleteFrame(int);
	void save(std::string, std::string);
	void load(std::string, std::string);
};
#endif // SPRITEEDITORVC_H
