#ifndef SPRITEEDITORVC_H
#define SPRITEEDITORVC_H

#include <QMainWindow>
#include <QScrollArea>
#include <QPushButton>
#include <QSlider>
#include <QLabel>

// TODO(gcpease): Add QRenderArea include

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


private:
	Ui::SpriteEditorVC *ui;
};
#endif // SPRITEEDITORVC_H
