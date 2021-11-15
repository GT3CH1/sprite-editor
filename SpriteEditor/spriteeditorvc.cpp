#include "spriteeditorvc.h"
#include "ui_spriteeditorvc.h"

SpriteEditorVC::SpriteEditorVC(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::SpriteEditorVC)
{
	ui->setupUi(this);
	this->setStyleSheet(QString("QMainWindow { background-color:white}"));
    // Set up FPS slider.
	colorDialog = new QColorDialog();
    ui->fpsSlider->setTickInterval(10);
    ui->fpsSlider->setSingleStep(10);
    ui->fpsSlider->setMaximum(60);
	ui->mainCanvas->setStyleSheet(QString("*{border: 1px solid;}"));
	connect(ui->customColorButtonChange, &QPushButton::released, this, &SpriteEditorVC::showColorDialog);
	connect(colorDialog,&QColorDialog::colorSelected, this, &SpriteEditorVC::updateCustomButtonColors);
	saveAction = new QAction(QIcon(":/res/save.svg"), tr("&Save..."), this);
	openAction = new QAction(QIcon(":/res/open.svg"), tr("&Open..."), this);
	closeAction = new QAction(QIcon(":/res/close.svg"), tr("&Close..."), this);
	createMenu();
	setupButtonColors();
}

SpriteEditorVC::~SpriteEditorVC()
{
	delete ui;
	delete colorDialog;
	delete saveAction;
	delete openAction;
	delete closeAction;
	delete helpAction;
	delete newFileAction;
	delete fileMenu;
	delete helpMenu;
}

/**
 * @brief Updates the FPS label
 * @param value
 */
void SpriteEditorVC::on_fpsSlider_valueChanged(int value)
{
    ui->fpsLabel->setText(QString::number(value));
	setupButtonColors();
}

/**
 * @brief Sets the given button color (via background-color) to the given hex value.
 * @param button - The button to change the color of.
 * @param hex - The hexadecimal string to change color to.
 */
void SpriteEditorVC::setButtonColor(QPushButton *button, QString hex)
{
	button->setStyleSheet(QString("QPushButton {background-color:%1;border:1px solid lightgray; border-radius:5px} QPushButton:hover{border: 1px solid gray;}").arg(hex));
}


/**
 * @brief Creates the top menu bar on the UI.
 */
void SpriteEditorVC::createMenu()
{
	saveAction = new QAction(QIcon::fromTheme(":/res/save.svg"), tr("&Save..."), this);
	openAction = new QAction(QIcon::fromTheme(":/res/open.svg"), tr("&Open..."), this);
	closeAction = new QAction(QIcon(":/res/close.svg"), tr("&Close..."), this);
	newFileAction = new QAction(QIcon(":/res/new.svg"), tr("&New..."), this);
	saveAction->setStatusTip(tr("Save this file"));
	openAction->setStatusTip(tr("Open an existing file"));
	closeAction->setStatusTip(tr("Close project"));
	newFileAction->setStatusTip(tr("Create a new file"));

	//TODO(GCPEASE): Attach this to the real signal and slots
//	connect(saveAction, &QAction::triggered, this, &SpriteEditorVC::showColorDialog);
//	connect(openAction, &QAction::triggered, this,  &SpriteEditorVC::showColorDialog);
//	connect(closeAction, &QAction::triggered, this,  &SpriteEditorVC::showColorDialog);
//	connect(newFileAction, &QAction::triggered, this,  &SpriteEditorVC::showColorDialog);
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newFileAction);
	fileMenu->addAction(saveAction);
	fileMenu->addAction(openAction);
	fileMenu->addSeparator();
	fileMenu->addAction(closeAction);
}


/**
 * @brief Sets all the button colors to the colors defined in QColorDialog.
 */
void SpriteEditorVC::setupButtonColors()
{
	setButtonColor(ui->primaryColorButton1,QColorDialog::standardColor(9).name(QColor::HexArgb));
	setButtonColor(ui->primaryColorButton2,QColorDialog::standardColor(21).name(QColor::HexArgb));
	setButtonColor(ui->primaryColorButton3,QColorDialog::standardColor(45).name(QColor::HexArgb));
	setButtonColor(ui->primaryColorButton4,QColorDialog::standardColor(36).name(QColor::HexArgb));
	setButtonColor(ui->primaryColorButton5,QColorDialog::standardColor(7).name(QColor::HexArgb));
	setButtonColor(ui->primaryColorButton6,QColorDialog::standardColor(5).name(QColor::HexArgb));
	setButtonColor(ui->primaryColorButton7,QColorDialog::standardColor(0).name(QColor::HexArgb));
	setButtonColor(ui->primaryColorButton8,QColorDialog::standardColor(47).name(QColor::HexArgb));
	updateCustomButtonColors();
}

/**
 * @brief Updates all of the custom color slots to match those in QColorDialog.
 */
void SpriteEditorVC::updateCustomButtonColors()
{
	setButtonColor(ui->customColorButton1,QColorDialog::customColor(0).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton2,QColorDialog::customColor(1).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton3,QColorDialog::customColor(2).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton4,QColorDialog::customColor(3).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton5,QColorDialog::customColor(4).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton6,QColorDialog::customColor(5).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton7,QColorDialog::customColor(6).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton8,QColorDialog::customColor(7).name(QColor::HexArgb));
}


void SpriteEditorVC::showColorDialog()
{
	colorDialog->show();
}
