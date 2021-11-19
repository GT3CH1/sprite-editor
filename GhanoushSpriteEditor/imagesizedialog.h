#ifndef IMAGESIZEDIALOG_H
#define IMAGESIZEDIALOG_H

#include <QDialog>

namespace Ui
{
class ImageSizeDialog;
}

class ImageSizeDialog : public QDialog
{
	Q_OBJECT

private:
	Ui::ImageSizeDialog *ui;
	int size;

public:
	explicit ImageSizeDialog(QWidget *parent = nullptr);
	~ImageSizeDialog();

signals:
	void dialogueComplete(int size);

private slots:
	void on_widthSpinBox_valueChanged(int arg1);

	void on_finishButton_clicked();


};

#endif // IMAGESIZEDIALOG_H
