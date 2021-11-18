#include "imagesizedialog.h"
#include "ui_imagesizedialog.h"

ImageSizeDialog::ImageSizeDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ImageSizeDialog)
{
	ui->setupUi(this);
}

ImageSizeDialog::~ImageSizeDialog()
{
	delete ui;
}

void ImageSizeDialog::on_widthSpinBox_valueChanged(int arg1)
{
	size = arg1;
}


void ImageSizeDialog::on_finishButton_clicked()
{
	emit dialogueComplete(size);
	accept();
}

