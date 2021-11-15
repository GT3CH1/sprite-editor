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
private slots:
    void on_fpsSlider_valueChanged(int value);

private:
	Ui::SpriteEditorVC *ui;
	QColorDialog colorDialog;
	void setButtonColor(QPushButton* button, QString hex);
	void createMenu();
	QAction *saveAction;
	QAction *openAction;
	QAction *closeAction;
	QAction *helpAction;
	QAction *newFileAction;
	QMenu *fileMenu;
	QMenu *helpMenu;
};
#endif // SPRITEEDITORVC_H
