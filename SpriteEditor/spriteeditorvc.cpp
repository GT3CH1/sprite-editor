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
//	ui->mainCanvas->setStyleSheet(QString("*{border: 1px solid;}"));
	model = new SpriteEditorModel();

	// Set up actions
	saveAction = new QAction(QIcon(":/res/save.svg"), tr("&Save..."), this);
	openAction = new QAction(QIcon(":/res/open.svg"), tr("&Open..."), this);
	closeAction = new QAction(QIcon(":/res/close.svg"), tr("&Close..."), this);
	newFileAction = new QAction(QIcon(":/res/new.svg"), tr("&New..."), this);
	helpAction = new QAction(tr("&Help..."),this);
	invertSelected = new QAction(tr("&Invert Brush"),this);
	rainbowBrushSelected = new QAction(tr("&Rainbow Brush"),this);
	softEraserSelected = new QAction(tr("&Soft Eraser"),this);
	hardPenSelected = new QAction(tr("&Pen"),this);
	hardEraserSelected = new QAction(tr("&Eraser"),this);
	softBrushSelected = new QAction(tr("&Brush"),this);
	connect(ui->customColorButtonChange, &QPushButton::released, this, &SpriteEditorVC::showColorDialog);
	connect(colorDialog,&QColorDialog::colorSelected, this, &SpriteEditorVC::updateCustomButtonColors);
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

	connect(ui->addFrameButton,&QPushButton::pressed,this->model,&SpriteEditorModel::addFrame);
	connect(&playbackUpdater, &QTimer::timeout,this,&SpriteEditorVC::updatePlaybackFrame);

	connect(this,&SpriteEditorVC::incrementToolSize, model, &SpriteEditorModel::incrementBrushSize);
	connect(this,&SpriteEditorVC::decrementToolSize, model, &SpriteEditorModel::decrementBrushSize);
	connect(this,&SpriteEditorVC::updateTool,this->model,&SpriteEditorModel::setActiveTool);
	connect(this,&SpriteEditorVC::colorChanged,this->model,&SpriteEditorModel::setActiveColor);
	connect(colorDialog,&QColorDialog::colorSelected, this->model, &SpriteEditorModel::setActiveColor);
	connect(this,&SpriteEditorVC::toggleGrid,ui->mainCanvas,&RenderArea::toggleGrid);

	connect(ui->brushToolButton,&QPushButton::pressed,this,&SpriteEditorVC::setSoftBrush);
	connect(ui->penToolButton,&QPushButton::pressed,this,&SpriteEditorVC::setHardPen);
	connect(ui->eraserToolButton,&QPushButton::pressed,this,&SpriteEditorVC::setHardEraser);
//	connect(ui->toolButton4,&QPushButton::pressed,this,&SpriteEditorVC::toolChanged);
	connect(this->model,&SpriteEditorModel::sendActiveFrame,ui->mainCanvas,&RenderArea::setImage);
	connect(ui->mainCanvas,&RenderArea::clicked, this->model,&SpriteEditorModel::drawing);
	connect(ui->mainCanvas,&RenderArea::released,this->model,&SpriteEditorModel::stopDrawing);
	connect(ui->mainCanvas,&RenderArea::clicked, this,&SpriteEditorVC::updatePreview);

	// Extra tools
	connect(invertSelected,&QAction::triggered,this,&SpriteEditorVC::setInvertBrush);
	connect(rainbowBrushSelected,&QAction::triggered,this,&SpriteEditorVC::setRainbowBrush);
	connect(softEraserSelected,&QAction::triggered,this,&SpriteEditorVC::setSoftEraser);
	connect(hardPenSelected,&QAction::triggered,this, &SpriteEditorVC::setHardPen);
	connect(softBrushSelected, &QAction::triggered,this,&SpriteEditorVC::setSoftBrush);
	connect(hardEraserSelected,&QAction::triggered,this,&SpriteEditorVC::setHardEraser);


	createMenu();
	setupButtonColors();

	ui->fpsSlider->setTickInterval(FPS_INTERVAL);
	ui->fpsSlider->setSingleStep(FPS_STEP);
	ui->fpsSlider->setMaximum(FPS_MAX);
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
	delete invertSelected;
	delete rainbowBrushSelected;
	delete softEraserSelected;
	delete hardEraserSelected;
	delete softBrushSelected;
	delete hardPenSelected;
}

/**
 * @brief Advances the animation playback frame
 */
void SpriteEditorVC::updatePreview()
{
	QPixmap currentFrame(model->getFramefromIndex(indexOfActiveFrame).scaled(128,128));
	ui->playbackCanvas->setImageScaled(currentFrame,128);
}

/**
 * @brief Advances the animation playback frame
 */
void SpriteEditorVC::updatePlaybackFrame()
{
	if(indexOfPlayback+1 > model->getFrameCount())
		indexOfPlayback = 0;
	QPixmap currentFrame(model->getFramefromIndex(indexOfPlayback++).scaled(128,128));
	ui->playbackCanvas->setImageScaled(currentFrame,128);
}

/**
 * @brief Updates the FPS label and controls the animation
 * playback timer
 * @param value
 */
void SpriteEditorVC::on_fpsSlider_valueChanged(int value)
{
    ui->fpsLabel->setText(QString::number(value));
	setupButtonColors();
	fps = value;

	if (fps == 0 && playbackUpdater.isActive())
	{
		playbackUpdater.stop();
	}
	else if (fps != 0)
	{
		if (!playbackUpdater.isActive())
		{
			playbackUpdater.start(1000 / fps);
		}
		else
		{
			playbackUpdater.setInterval(1000 / fps);
		}
	}
}

/**
 * @brief Launches the "Save File" dialog window and prompts the user
 * to choose a name and location for saving the active sprite. The file
 * path and name will be passed to the model.
 */
void SpriteEditorVC::savePressed()
{
	path = QFileDialog::getSaveFileName(this, tr("Save File"), path, tr(FILE_FILTER));
	std::string pathAsString(path.toStdString());

	// Find the index of the last "/" character
	auto i(pathAsString.find_last_of("/"));

	// Separate the path and file name
	if (i != std::string::npos)
	{
		path = QString::fromStdString(pathAsString.substr(0, i + 1));
		std::string name(pathAsString.substr(i + 1));
		emit save(path.toStdString(), name);
	}
}

/**
 * @brief Launches the "Open File" dialog window and prompts the user
 * to choose a file to open and replace the active sprite. The file
 * path and name will be passed to the model.
 */
void SpriteEditorVC::loadPressed()
{
	path = QFileDialog::getOpenFileName(this, tr("Open File"), path, tr(FILE_FILTER));
	std::string pathAsString(path.toStdString());

	// Find the index of the last "/" character
	auto i(pathAsString.find_last_of("/"));

	// Separate the path and file name
	if (i != std::string::npos)
	{
		path = QString::fromStdString(pathAsString.substr(0, i + 1));
		std::string name(pathAsString.substr(i + 1));
		emit load(path.toStdString(), name);
	}
}

/**
 * @brief Triggers when any key is pressed and emits any
 * relevant signals.
 * @param event
 */
void SpriteEditorVC::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	// Decrease tool size
	case Qt::Key_BracketLeft:
		emit decrementToolSize();
		break;
	// Increase tool size
	case Qt::Key_BracketRight:
		emit incrementToolSize();
		break;
	// Save the file
	case Qt::Key_S:
		if (event->modifiers() == Qt::ControlModifier)
		{
			savePressed();
		}
		break;
	// Open a file
	case Qt::Key_O:
		if (event->modifiers() == Qt::ControlModifier)
		{
			loadPressed();
		}
		break;
	// Move to previous frame (if it exists)
	case Qt::Key_Left:
		if (indexOfActiveFrame > 0)
		{
			emit changeActiveFrame(indexOfActiveFrame - 1);
		}
		break;
	// Move to next frame (if it exists)
	case Qt::Key_Right:
		//TODO(JVielstich): Get frame count from model
		break;
	// Toggles if the grid is shown.
    case Qt::Key_G:
        emit toggleGrid();
        break;
	default:
		// do nothing
		break;
	}
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
	helpAction->setStatusTip(tr("Help"));
	saveAction->setStatusTip(tr("Save this file"));
	openAction->setStatusTip(tr("Open an existing file"));
	closeAction->setStatusTip(tr("Close project"));
	newFileAction->setStatusTip(tr("Create a new file"));

	fileMenu = menuBar()->addMenu(tr("&File"));
	toolsMenu = menuBar()->addMenu(tr("&Tools"));
	helpMenu = menuBar()->addMenu(tr("&Help"));
	fileMenu->addAction(newFileAction);
	fileMenu->addAction(saveAction);
	fileMenu->addAction(openAction);
	fileMenu->addSeparator();
	fileMenu->addAction(closeAction);
	helpMenu->addAction(helpAction);

	toolsMenu->addAction(invertSelected);
	toolsMenu->addAction(rainbowBrushSelected);
	toolsMenu->addAction(softEraserSelected);
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

void SpriteEditorVC::setInvertBrush()
{
	emit updateTool(SpriteEditorModel::ToolType::InvertBrush);
}

void SpriteEditorVC::setRainbowBrush()
{
	emit updateTool(SpriteEditorModel::ToolType::Rainbow);
}

void SpriteEditorVC::setSoftEraser()
{
	emit updateTool(SpriteEditorModel::ToolType::SoftEraser);
}

void SpriteEditorVC::setHardPen()
{
	emit updateTool(SpriteEditorModel::ToolType::Pen);
}

void SpriteEditorVC::setSoftBrush()
{
	emit updateTool(SpriteEditorModel::ToolType::Brush);
}

void SpriteEditorVC::setHardEraser()
{
	emit updateTool(SpriteEditorModel::ToolType::HardEraser);
}
