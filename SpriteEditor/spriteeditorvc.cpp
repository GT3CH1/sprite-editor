#include "spriteeditorvc.h"
#include "ui_spriteeditorvc.h"

SpriteEditorVC::SpriteEditorVC(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::SpriteEditorVC)
{
	ui->setupUi(this);
}

SpriteEditorVC::~SpriteEditorVC()
{
	delete ui;
}


void SpriteEditorVC::on_fpsSlider_valueChanged(int value)
{
    ui->currentFpsLabel->setText(QString::number(value));
}

