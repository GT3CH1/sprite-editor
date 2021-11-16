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
	model = new SpriteEditorModel();
	connect(ui->customColorButtonChange, &QPushButton::released, this, &SpriteEditorVC::showColorDialog);
	connect(colorDialog,&QColorDialog::colorSelected, this, &SpriteEditorVC::updateCustomButtonColors);
	connect(this,&SpriteEditorVC::colorChanged,this->model,&SpriteEditorModel::setActiveColor);

	// Sets up the getting when a color button is clicked.
	connect(ui->primaryColorButton1,&QPushButton::pressed,this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->primaryColorButton2,&QPushButton::pressed,this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->primaryColorButton3,&QPushButton::pressed,this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->primaryColorButton4,&QPushButton::pressed,this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->primaryColorButton5,&QPushButton::pressed,this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->primaryColorButton6,&QPushButton::pressed,this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->primaryColorButton7,&QPushButton::pressed,this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->primaryColorButton8,&QPushButton::pressed,this, &SpriteEditorVC::colorButtonClicked);

	connect(ui->customColorButton1,&QPushButton::pressed,this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->customColorButton2,&QPushButton::pressed,this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->customColorButton3,&QPushButton::pressed,this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->customColorButton4,&QPushButton::pressed,this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->customColorButton5,&QPushButton::pressed,this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->customColorButton6,&QPushButton::pressed,this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->customColorButton7,&QPushButton::pressed,this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->customColorButton8,&QPushButton::pressed,this, &SpriteEditorVC::colorButtonClicked);

	connect(ui->brushToolButton,&QPushButton::pressed,this,&SpriteEditorVC::toolChanged);
	connect(ui->penToolButton,&QPushButton::pressed,this,&SpriteEditorVC::toolChanged);
	connect(ui->eraserToolButton,&QPushButton::pressed,this,&SpriteEditorVC::toolChanged);
	connect(ui->toolButton4,&QPushButton::pressed,this,&SpriteEditorVC::toolChanged);
	connect(this,&SpriteEditorVC::updateTool,this->model,&SpriteEditorModel::setActiveTool);

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
	setButtonColor(ui->primaryColorButton1,colorDialog->standardColor(9).name(QColor::HexArgb));
	setButtonColor(ui->primaryColorButton2,colorDialog->standardColor(21).name(QColor::HexArgb));
	setButtonColor(ui->primaryColorButton3,colorDialog->standardColor(45).name(QColor::HexArgb));
	setButtonColor(ui->primaryColorButton4,colorDialog->standardColor(36).name(QColor::HexArgb));
	setButtonColor(ui->primaryColorButton5,colorDialog->standardColor(7).name(QColor::HexArgb));
	setButtonColor(ui->primaryColorButton6,colorDialog->standardColor(5).name(QColor::HexArgb));
	setButtonColor(ui->primaryColorButton7,colorDialog->standardColor(0).name(QColor::HexArgb));
	setButtonColor(ui->primaryColorButton8,colorDialog->standardColor(47).name(QColor::HexArgb));
	updateCustomButtonColors();
}

/**
 * @brief Updates all of the custom color slots to match those in QColorDialog.
 */
void SpriteEditorVC::updateCustomButtonColors()
{
	setButtonColor(ui->customColorButton1,colorDialog->customColor(0).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton2,colorDialog->customColor(1).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton3,colorDialog->customColor(2).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton4,colorDialog->customColor(3).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton5,colorDialog->customColor(4).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton6,colorDialog->customColor(5).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton7,colorDialog->customColor(6).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton8,colorDialog->customColor(7).name(QColor::HexArgb));
}


/**
 * @brief Shows the color picker.
 */
void SpriteEditorVC::showColorDialog()
{
	colorDialog->setOption(QColorDialog::ShowAlphaChannel);
	colorDialog->show();
}

/**
 * @brief Handles setting the new color when one of the color buttons is clicked.
 */
void SpriteEditorVC::colorButtonClicked(){
	// Please, c++. Let us use switch on strings. This is absurd.
	QColor c;
	std::string name(sender()->objectName().toStdString());
	if(name == "primaryColorButton1")
		c = QColorDialog::standardColor(9);
	else if(name == "primaryColorButton2")
		c = QColorDialog::standardColor(21);
	else if (name == "primaryColorButton3")
		c = QColorDialog::standardColor(45);
	else if (name == "primaryColorButton4")
		c = QColorDialog::standardColor(36);
	else if (name == "primaryColorButton5")
		c = QColorDialog::standardColor(7);
	else if (name == "primaryColorButton6")
		c = QColorDialog::standardColor(5);
	else if (name == "primaryColorButton7")
		c = QColorDialog::standardColor(0);
	else if (name == "primaryColorButton8")
		c = QColorDialog::standardColor(47);
	else if (name == "customColorButton1")
		c = QColorDialog::customColor(0);
	else if (name == "customColorButton2")
		c = QColorDialog::customColor(1);
	else if (name == "customColorButton3")
		c = QColorDialog::customColor(2);
	else if (name == "customColorButton4")
		c = QColorDialog::customColor(3);
	else if (name == "customColorButton5")
		c = QColorDialog::customColor(4);
	else if (name == "customColorButton6")
		c = QColorDialog::customColor(5);
	else if (name == "customColorButton7")
		c = QColorDialog::customColor(6);
	else if (name == "customColorButton8")
		c = QColorDialog::customColor(7);
	emit colorChanged(c);
}

/**
 * @brief Changes the current tool based on what was clicked.
 */
void SpriteEditorVC::toolChanged()
{
	SpriteEditorModel::ToolType tool = SpriteEditorModel::ToolType::Brush;
	std::string name(sender()->objectName().toStdString());
	if(name == "penToolButton")
		tool = SpriteEditorModel::ToolType::Pen;
	else if(name == "brushToolButton")
		tool = SpriteEditorModel::ToolType::Brush;
	//TODO(GCPEASE): Implement rest of tool buttons
	else if(name == "eraserToolButton")
		tool = SpriteEditorModel::ToolType::HardEraser;
	emit updateTool(tool);
}
