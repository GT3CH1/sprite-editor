#include "spriteeditorvc.h"
#include "ui_spriteeditorvc.h"

SpriteEditorVC::SpriteEditorVC(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::SpriteEditorVC)
{
	ui->setupUi(this);
    this->setStyleSheet(QString("QMainWindow { background-color:white}"));
    // Set up FPS slider.
    ui->fpsSlider->setTickInterval(10);
    ui->fpsSlider->setSingleStep(10);
    ui->fpsSlider->setMaximum(60);
	qDebug() << ui->primaryColorButton1->styleSheet();
}

SpriteEditorVC::~SpriteEditorVC()
{
	delete ui;
}

/**
 * @brief Updates the FPS label
 * @param value
 */
void SpriteEditorVC::on_fpsSlider_valueChanged(int value)
{
    ui->fpsLabel->setText(QString::number(value));
}

