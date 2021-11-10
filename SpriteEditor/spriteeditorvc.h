#ifndef SPRITEEDITORVC_H
#define SPRITEEDITORVC_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SpriteEditorVC; }
QT_END_NAMESPACE

class SpriteEditorVC : public QMainWindow
{
	Q_OBJECT

public:
	SpriteEditorVC(QWidget *parent = nullptr);
	~SpriteEditorVC();

private:
	Ui::SpriteEditorVC *ui;
};
#endif // SPRITEEDITORVC_H
