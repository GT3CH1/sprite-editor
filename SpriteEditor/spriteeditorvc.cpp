#include "spriteeditorvc.h"

SpriteEditorVC::SpriteEditorVC(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::SpriteEditorVC)
	, imageSizeDialogue(this)
{
	ui->setupUi(this);
	this->setStyleSheet(QString("QMainWindow { background-color:white}"));
	ui->mainCanvas->setStyleSheet(QString("RenderArea { border:1px solid gray}"));
	ui->playbackCanvas->setStyleSheet(QString("RenderArea { border:1px solid gray}"));
	model = new SpriteEditorModel();
	// Set up FPS slider.
	ui->fpsSlider->setTickInterval(FPS_INTERVAL);
	ui->fpsSlider->setSingleStep(FPS_STEP);
	ui->fpsSlider->setMaximum(FPS_MAX);
	// Set up frame preview area
	framePreviewLayout = new QHBoxLayout;
	ui->frameDisplay->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	ui->frameDisplay->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->frameDisplay->setWidgetResizable(true);
	ui->scrollAreaWidgetContents->setLayout(framePreviewLayout);
	ui->scrollAreaWidgetContents->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	colorDialog = new QColorDialog();
	model = new SpriteEditorModel();
	createMenu();
	setupButtonColors();
	connect(ui->customColorButtonChange, &QPushButton::released, this, &SpriteEditorVC::showColorDialog);
	connect(colorDialog, &QColorDialog::colorSelected, this, &SpriteEditorVC::updateCustomButtonColors);
	// UI to Control
	// Default Colors - No, Gavin did not type this out by hand but used a script.
	connect(ui->primaryColorButton1, &QPushButton::pressed, this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->primaryColorButton2, &QPushButton::pressed, this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->primaryColorButton3, &QPushButton::pressed, this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->primaryColorButton4, &QPushButton::pressed, this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->primaryColorButton5, &QPushButton::pressed, this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->primaryColorButton6, &QPushButton::pressed, this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->primaryColorButton7, &QPushButton::pressed, this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->primaryColorButton8, &QPushButton::pressed, this, &SpriteEditorVC::colorButtonClicked);
	// Custom Colors
	connect(ui->customColorButton1, &QPushButton::pressed, this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->customColorButton2, &QPushButton::pressed, this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->customColorButton3, &QPushButton::pressed, this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->customColorButton4, &QPushButton::pressed, this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->customColorButton5, &QPushButton::pressed, this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->customColorButton6, &QPushButton::pressed, this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->customColorButton7, &QPushButton::pressed, this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->customColorButton8, &QPushButton::pressed, this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->customColorButton9, &QPushButton::pressed, this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->customColorButton10, &QPushButton::pressed, this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->customColorButton11, &QPushButton::pressed, this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->customColorButton12, &QPushButton::pressed, this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->customColorButton13, &QPushButton::pressed, this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->customColorButton14, &QPushButton::pressed, this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->customColorButton15, &QPushButton::pressed, this, &SpriteEditorVC::colorButtonClicked);
	connect(ui->customColorButton16, &QPushButton::pressed, this, &SpriteEditorVC::colorButtonClicked);
	// Menu Buttons
	connect(saveAction, &QAction::triggered, this, &SpriteEditorVC::savePressed);
	connect(openAction, &QAction::triggered, this, &SpriteEditorVC::loadPressed);
	// Other
	connect(ui->addFrameButton, &QPushButton::clicked, this->model, &SpriteEditorModel::addFrame);
	connect(ui->deleteFrameButton, &QPushButton::clicked, this, &SpriteEditorVC::deleteFrame);
	connect(ui->clearFrameButton,&QPushButton::clicked,this->model, &SpriteEditorModel::clearFrame);
	// UI to Model
	connect(ui->mainCanvas, &RenderArea::clicked, model, &SpriteEditorModel::drawing);
	connect(ui->duplicateFrameButton, &QPushButton::clicked, model, &SpriteEditorModel::duplicateFrame);
	connect(this, &SpriteEditorVC::duplicateFrame, model, &SpriteEditorModel::duplicateFrame);
	connect(this, &SpriteEditorVC::clearFrame, model, &SpriteEditorModel::clearFrame);
	connect(this, &SpriteEditorVC::addNewFrame, model, &SpriteEditorModel::addFrame);
	connect(this, &SpriteEditorVC::deleteActiveFrame, model, &SpriteEditorModel::deleteFrame);
	connect(this, &SpriteEditorVC::incrementToolSize, model, &SpriteEditorModel::incrementBrushSize);
	connect(this, &SpriteEditorVC::decrementToolSize, model, &SpriteEditorModel::decrementBrushSize);
	connect(this, &SpriteEditorVC::updateTool, this->model, &SpriteEditorModel::setActiveTool);
	connect(this, &SpriteEditorVC::colorChanged, this->model, &SpriteEditorModel::setActiveColor);
	connect(colorDialog, &QColorDialog::colorSelected, this->model, &SpriteEditorModel::setActiveColor);
	connect(this, &SpriteEditorVC::toggleGrid, ui->mainCanvas, &RenderArea::toggleGrid);
	// Tool changes
	connect(ui->brushToolButton, &QPushButton::pressed, this, &SpriteEditorVC::setSoftBrush);
	connect(ui->penToolButton, &QPushButton::pressed, this, &SpriteEditorVC::setHardPen);
	connect(ui->eraserToolButton, &QPushButton::pressed, this, &SpriteEditorVC::setHardEraser);
	connect(ui->softEraserButton, &QPushButton::pressed, this, &SpriteEditorVC::setSoftEraser);
	connect(ui->gaussianButton, &QPushButton::pressed, this, &SpriteEditorVC::setGaussian);
	connect(ui->invertButton, &QPushButton::pressed, this, &SpriteEditorVC::setInvertBrush);
	connect(ui->rainbowButton, &QPushButton::pressed, this, &SpriteEditorVC::setRainbowBrush);
	connect(ui->sprayCanButton, &QPushButton::pressed, this, &SpriteEditorVC::setSprayCan);
	connect(ui->mainCanvas, &RenderArea::released, this->model, &SpriteEditorModel::stopDrawing);
	// Extra tools
	connect(invertSelected, &QAction::triggered, this, &SpriteEditorVC::setInvertBrush);
	connect(rainbowBrushSelected, &QAction::triggered, this, &SpriteEditorVC::setRainbowBrush);
	connect(softEraserSelected, &QAction::triggered, this, &SpriteEditorVC::setSoftEraser);
	connect(hardPenSelected, &QAction::triggered, this, &SpriteEditorVC::setHardPen);
	connect(softBrushSelected, &QAction::triggered, this, &SpriteEditorVC::setSoftBrush);
	connect(hardEraserSelected, &QAction::triggered, this, &SpriteEditorVC::setHardEraser);
	connect(sprayCanSelected, &QAction::triggered, this, &SpriteEditorVC::setSprayCan);
	connect(rainbowSpraycanSelected, &QAction::triggered, this, &SpriteEditorVC::setRainbowSpraycan);
	connect(gaussianSelected, &QAction::triggered, this, &SpriteEditorVC::setGaussian);
	connect(gridSelected, &QAction::triggered, ui->mainCanvas, &RenderArea::toggleGrid);
	connect(newFileAction, &QAction::triggered, this, &SpriteEditorVC::startSizeDialogue);
	// Model to UI
	connect(this->model, &SpriteEditorModel::sendActiveFrame, ui->mainCanvas, &RenderArea::setImage);
	connect(this->model, &SpriteEditorModel::brushSizeChanged, this, &SpriteEditorVC::setBrushSizeLabel);
	// Model to Control
	connect(model, &SpriteEditorModel::sendFrames, this, &SpriteEditorVC::previewFrames);
	connect(model, &SpriteEditorModel::sendActiveFrameIndex, this, &SpriteEditorVC::updateActivePreview);
	connect(model, &SpriteEditorModel::sendActiveFrameIndex, this, &SpriteEditorVC::updateActiveFrame);
	// Internal
	connect(&playbackUpdater, &QTimer::timeout, this, &SpriteEditorVC::updatePlaybackFrame);
	// Control to Model
	connect(this, &SpriteEditorVC::incrementToolSize, model, &SpriteEditorModel::incrementBrushSize);
	connect(this, &SpriteEditorVC::decrementToolSize, model, &SpriteEditorModel::decrementBrushSize);
	connect(ui->toolSizeSlider, &QSlider::valueChanged, model, &SpriteEditorModel::setToolSize);
	connect(this, &SpriteEditorVC::updateTool, this->model, &SpriteEditorModel::setActiveTool);
	connect(this, &SpriteEditorVC::colorChanged, this->model, &SpriteEditorModel::setActiveColor);
	connect(colorDialog, &QColorDialog::colorSelected, this->model, &SpriteEditorModel::setActiveColor);
	connect(this, &SpriteEditorVC::save, model, &SpriteEditorModel::save);
	connect(this, &SpriteEditorVC::load, model, &SpriteEditorModel::load);
	connect(this->model, &SpriteEditorModel::sendFrames, model, &SpriteEditorModel::setFrames);
	connect(this, &SpriteEditorVC::changeActiveFrame, model, &SpriteEditorModel::changeActiveFrame);
	connect(this, &SpriteEditorVC::remove, model, &SpriteEditorModel::deleteFrame);
	connect(&imageSizeDialogue, &ImageSizeDialog::dialogueComplete, this, &SpriteEditorVC::finishSizeDialogue);
	connect(this->model, &SpriteEditorModel::updateCanvasSize, ui->mainCanvas, &RenderArea::setCanvasSize);
	connect(this->model, &SpriteEditorModel::updateCanvasSize, ui->toolSizeSlider, &QSlider::setMaximum);
	imageSizeDialogue.setModal(true);
	updateActivePreview(0);
	setHardPen();
	emit colorChanged(QColorDialog::standardColor(RED));
}

SpriteEditorVC::~SpriteEditorVC()
{
	delete ui;
	delete model;
	delete colorDialog;
	delete saveAction;
	delete openAction;
	delete newFileAction;
	delete fileMenu;
	delete invertSelected;
	delete rainbowBrushSelected;
	delete softEraserSelected;
	delete hardEraserSelected;
	delete softBrushSelected;
	delete hardPenSelected;
	delete sprayCanSelected;
	delete rainbowSpraycanSelected;
}

// UI SETUP

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
	// Set up tools
	invertSelected = new QAction(QIcon(INVERT_SVG_PATH), tr("&Invert Brush"), this);
	rainbowBrushSelected = new QAction(QIcon(RAINBOW_SVG_PATH), tr("&Rainbow Brush"), this);
	softEraserSelected = new QAction(QIcon(SOFT_ERASER_PATH), tr("S&oft Eraser"), this);
	hardPenSelected = new QAction(QIcon(PEN_SVG_PATH), tr("&Pen"), this);
	hardEraserSelected = new QAction(QIcon(ERASER_SVG_PATH), tr("&Eraser"), this);
	softBrushSelected = new QAction(QIcon(SOFT_BRUSH_PATH), tr("&Brush"), this);
	sprayCanSelected = new QAction(QIcon(SPRAY_CAN_SVG_PATH), tr("&Spray Can"), this);
	gaussianSelected = new QAction(QIcon(BLUR_SVG_PATH), tr("Ga&ussian Blur"), this);
	gridSelected = new QAction(QIcon(GRID_SVG_PATH), tr("&Grid"), this);
	saveAction = new QAction(QIcon(SAVE_SVG_PATH), tr("&Save..."), this);
	openAction = new QAction(QIcon(OPEN_SVG_PATH), tr("&Open..."), this);
	newFileAction = new QAction(QIcon(NEW_SVG_PATH), tr("&New..."), this);
	rainbowSpraycanSelected = new QAction(QIcon(SPRAY_CAN_SVG_PATH), tr("R&ainbow Spraycan"),this);

	saveAction->setStatusTip(tr("Save this file"));
	openAction->setStatusTip(tr("Open an existing file"));
	newFileAction->setStatusTip(tr("Create a new file"));
	fileMenu = menuBar()->addMenu(tr("&File"));
	toolsMenu = menuBar()->addMenu(tr("&Tools"));
	fileMenu->addAction(newFileAction);
	fileMenu->addAction(saveAction);
	fileMenu->addAction(openAction);
	toolsMenu->addAction(invertSelected);
	toolsMenu->addAction(rainbowBrushSelected);
	toolsMenu->addAction(hardPenSelected);
	toolsMenu->addAction(softEraserSelected);
	toolsMenu->addAction(hardEraserSelected);
	toolsMenu->addAction(softBrushSelected);
	toolsMenu->addAction(sprayCanSelected);
	toolsMenu->addAction(rainbowSpraycanSelected);
	toolsMenu->addAction(gaussianSelected);
	toolsMenu->addAction(gridSelected);
}


/**
 * @brief Sets all the button colors to the colors defined in QColorDialog.
 */
void SpriteEditorVC::setupButtonColors()
{
	setButtonColor(ui->primaryColorButton1, colorDialog->standardColor(RED).name(QColor::HexArgb));
	setButtonColor(ui->primaryColorButton2, colorDialog->standardColor(ORANGE).name(QColor::HexArgb));
	setButtonColor(ui->primaryColorButton3, colorDialog->standardColor(YELLOW).name(QColor::HexArgb));
	setButtonColor(ui->primaryColorButton4, colorDialog->standardColor(GREEN).name(QColor::HexArgb));
	setButtonColor(ui->primaryColorButton5, colorDialog->standardColor(PURPLE).name(QColor::HexArgb));
	setButtonColor(ui->primaryColorButton6, colorDialog->standardColor(BLUE).name(QColor::HexArgb));
	setButtonColor(ui->primaryColorButton7, colorDialog->standardColor(BLACK).name(QColor::HexArgb));
	setButtonColor(ui->primaryColorButton8, colorDialog->standardColor(WHITE).name(QColor::HexArgb));
	updateCustomButtonColors();
}

/**
 * @brief Updates all of the custom color slots to match those in QColorDialog.
 */
void SpriteEditorVC::updateCustomButtonColors()
{
	setButtonColor(ui->customColorButton1, colorDialog->customColor(0).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton2, colorDialog->customColor(1).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton3, colorDialog->customColor(2).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton4, colorDialog->customColor(3).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton5, colorDialog->customColor(4).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton6, colorDialog->customColor(5).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton7, colorDialog->customColor(6).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton8, colorDialog->customColor(7).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton9, colorDialog->customColor(8).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton10, colorDialog->customColor(9).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton11, colorDialog->customColor(10).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton12, colorDialog->customColor(11).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton13, colorDialog->customColor(12).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton14, colorDialog->customColor(13).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton15, colorDialog->customColor(14).name(QColor::HexArgb));
	setButtonColor(ui->customColorButton16, colorDialog->customColor(15).name(QColor::HexArgb));
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
 * @brief Advances the animation playback frame
 */
void SpriteEditorVC::updatePlaybackFrame()
{
	if (indexOfPlayback + 1 > model->getFrameCount())
		indexOfPlayback = 0;

	QPixmap currentFrame(model->getFramefromIndex(indexOfPlayback++).scaled(PREVIEW_SIZE, PREVIEW_SIZE));
	ui->playbackCanvas->setImageScaled(currentFrame, PREVIEW_SIZE);
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
	// Return focus to main window
	this->setFocus();

	if (fps == 0 && playbackUpdater.isActive())
		playbackUpdater.stop();

	else if (fps != 0)
	{
		if (!playbackUpdater.isActive())
			playbackUpdater.start(1000 / fps);

		else
			playbackUpdater.setInterval(1000 / fps);
	}
}


/**
 * @brief Displays the frames in the frame selection bar below the main canvas
 * @param allFrames
 */
void SpriteEditorVC::previewFrames()
{
	if (framePreviewLayout->count() > 0)
	{
			QLayoutItem* item;
			while ((item = framePreviewLayout->takeAt(0)) != NULL)
			{
				delete item->widget();
				delete item;
			}
	}

	for (int i = 0; i < model->getFrameCount(); i++)
	{
		RenderArea *newWidget = new RenderArea;
		newWidget->setImageScaled(model->getFramefromIndex(i), FRAME_SIZE);
		framePreviewLayout->addWidget(newWidget);
	}
}

/**
 * @brief Updates the frame preview of the active frame as the user edits it
 * @param activeFrameIndex
 */
void SpriteEditorVC::updateActivePreview(int activeFrameIndex)
{
	RenderArea *newPreview = new RenderArea;
	newPreview->setImageScaled(model->getFramefromIndex(activeFrameIndex), FRAME_SIZE);
	QLayoutItem* item;
	if ((item = framePreviewLayout->takeAt(activeFrameIndex)) != NULL)
	{
		delete item->widget();
		delete item;
	}
	framePreviewLayout->insertWidget(activeFrameIndex, newPreview);
}

/**
 * @brief Changes the active frame to the one selected
 */
void SpriteEditorVC::sendActiveFrame()
{
	for (int i = 0; i < model->getFrameCount(); i++)
	{
		std::string frameName(framePreviews.at(i)->objectName().toStdString());
		std::string senderName(sender()->objectName().toStdString());

		if (frameName == senderName)
		{
			if (i != indexOfActiveFrame)
				emit changeActiveFrame(i);

			break;
		}
	}
}

/**
 * @brief Sets the main canvas to the active frame
 * @param activeFrameIndex
 */
void SpriteEditorVC::updateActiveFrame(int activeFrameIndex)
{
	QString labelString = QString("Frame %1/%2").arg(activeFrameIndex + 1).arg(model->getFrameCount());
	ui->frameLabel->setText(labelString);
	indexOfActiveFrame = activeFrameIndex;
	ui->mainCanvas->setImage(model->getFramefromIndex(activeFrameIndex));
}

/**
 * @brief Tells the Model to delete the current frame
 */
void SpriteEditorVC::deleteFrame()
{
	emit remove(indexOfActiveFrame);
}

/**
 * @brief Tells the Model to add a frame to the end of the sprite
 */
void SpriteEditorVC::addFrame()
{
	emit add();
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
		// Remove any instances of .ssp from the file name
		auto j = name.find(".ssp");

		while (j != std::string::npos)
		{
			name.erase(j, 4);
			j = name.find(".ssp");
		}

		emit load(path.toStdString(), name);
	}
}

/**
 * @brief Handles setting the new color when one of the color buttons is clicked.
 */
void SpriteEditorVC::colorButtonClicked()
{
	// Please, c++. Let us use switch on strings. This is absurd.
	QColor c;
	std::string name(sender()->objectName().toStdString());

	if (name == "primaryColorButton1")
		c = QColorDialog::standardColor(RED);

	else if (name == "primaryColorButton2")
		c = QColorDialog::standardColor(ORANGE);

	else if (name == "primaryColorButton3")
		c = QColorDialog::standardColor(YELLOW);

	else if (name == "primaryColorButton4")
		c = QColorDialog::standardColor(GREEN);

	else if (name == "primaryColorButton5")
		c = QColorDialog::standardColor(PURPLE);

	else if (name == "primaryColorButton6")
		c = QColorDialog::standardColor(BLUE);

	else if (name == "primaryColorButton7")
		c = QColorDialog::standardColor(BLACK);

	else if (name == "primaryColorButton8")
		c = QColorDialog::standardColor(WHITE);

	for (int i = 0 ; i < 16; i++)
	{
		QString buttonName = QString("customColorButton%1").arg(i + 1);

		if (name == buttonName.toStdString())
			c = QColorDialog::customColor(i);
	}

	emit colorChanged(c);
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
				savePressed();
			else
				sprayCanSelected->trigger();
			break;

		// Open a file
		case Qt::Key_O:
			if (event->modifiers() == Qt::ControlModifier)
				loadPressed();
			else
				softEraserSelected->trigger();
			break;

		// Open a file
		case Qt::Key_N:
			if (event->modifiers() == Qt::ControlModifier)
				newFileAction->trigger();
		break;

		// Move to previous frame (if it exists)
		case Qt::Key_Left:
			if (indexOfActiveFrame > 0)
				emit changeActiveFrame(indexOfActiveFrame - 1);

			break;

		// Move to next frame (if it exists)
		case Qt::Key_Right:
			if (indexOfActiveFrame < model->getFrameCount() - 1)
				emit changeActiveFrame(indexOfActiveFrame + 1);

			break;

		// Toggles if the grid is shown.
		case Qt::Key_G:
			emit toggleGrid();
			break;

		case Qt::Key_A:
			if (event->modifiers() == Qt::ControlModifier)
				emit addNewFrame();
			else
				rainbowSpraycanSelected->trigger();
		break;

		case Qt::Key_Delete:
			emit deleteActiveFrame(indexOfActiveFrame);
			break;

		case Qt::Key_D:
			if (event->modifiers() == Qt::ControlModifier)
				emit duplicateFrame();
			break;

		case Qt::Key_C:
			if (event->modifiers() == Qt::ControlModifier)
				emit clearFrame();
			break;

		case Qt::Key_I:
			invertSelected->trigger();
			break;

		case Qt::Key_R:
			rainbowBrushSelected->trigger();
			break;
		case Qt::Key_P:
			hardPenSelected->trigger();
			break;
		case Qt::Key_E:
			hardEraserSelected->trigger();
			break;
		case Qt::Key_B:
			softBrushSelected->trigger();
			break;
		case Qt::Key_U:
			gaussianSelected->trigger();
			break;
		default:
			// do nothing
			break;
	}
}

/**
 * @brief Sets the current brush to the invert brush.
 */
void SpriteEditorVC::setInvertBrush()
{
	emit updateTool(SpriteEditorModel::ToolType::InvertBrush);
	setCustomCursor(INVERT_SVG_PATH);
}

/**
 * @brief Sets the current brush to the rainbow brush.
 */
void SpriteEditorVC::setRainbowBrush()
{
	emit updateTool(SpriteEditorModel::ToolType::Rainbow);
	setCustomCursor(RAINBOW_SVG_PATH);
}

/**
 * @brief Sets the current tool to the soft eraser.
 */
void SpriteEditorVC::setSoftEraser()
{
	emit updateTool(SpriteEditorModel::ToolType::SoftEraser);
	setCustomCursor(SOFT_ERASER_PATH);
}

/**
 * @brief Sets the current tool to the hard pen.
 */
void SpriteEditorVC::setHardPen()
{
	emit updateTool(SpriteEditorModel::ToolType::Pen);
	setCustomCursor(PEN_SVG_PATH);
}

/**
 * @brief Sets the current tool to the soft brush.
 */
void SpriteEditorVC::setSoftBrush()
{
	emit updateTool(SpriteEditorModel::ToolType::Brush);
	setCustomCursor(SOFT_BRUSH_PATH);
}

/**
 * @brief Sets the current tool to the hard eraser.
 */
void SpriteEditorVC::setHardEraser()
{
	emit updateTool(SpriteEditorModel::ToolType::HardEraser);
	setCustomCursor(ERASER_SVG_PATH);
}

/**
 * @brief Sets the current tool to the spray can.
 */
void SpriteEditorVC::setSprayCan()
{
	emit updateTool(SpriteEditorModel::ToolType::SprayCan);
	setCustomCursor(SPRAY_CAN_SVG_PATH);
}

/**
 * @brief Sets the current tool to the gaussian blur tool.
 */
void SpriteEditorVC::setGaussian()
{
	emit updateTool(SpriteEditorModel::ToolType::Gaussian);
	setCustomCursor(BLUR_SVG_PATH);
}

void SpriteEditorVC::setRainbowSpraycan()
{
	emit updateTool(SpriteEditorModel::ToolType::RainbowSprayCan);
	setCustomCursor(SPRAY_CAN_SVG_PATH);
}

/**
 * @brief Advance the frame for the frame preview
 */
void SpriteEditorVC::on_nextFrameButton_clicked()
{
	if (indexOfActiveFrame < model->getFrameCount() - 1)
		emit changeActiveFrame(indexOfActiveFrame + 1);
}

/**
 * @brief Make the frame for the preview go back a frame.
 */
void SpriteEditorVC::on_lastFrameButton_clicked()
{
	if (indexOfActiveFrame > 0)
		emit changeActiveFrame(indexOfActiveFrame - 1);
}

/**
 * @brief Show the new sprite dialgoue.
 */
void SpriteEditorVC::startSizeDialogue()
{
	imageSizeDialogue.exec();
}

/**
 * @brief Sets the size of the sprite from the data given from size dialogue.
 * @param size - the new size of everything.
 */
void SpriteEditorVC::finishSizeDialogue(int size)
{
	activateWindow();
	model->setSize(size, size);
}

void SpriteEditorVC::setBrushSizeLabel(int size)
{
	ui->toolSizeSlider->setValue(size);
	QString labelString = QString("Stroke Size: %1px").arg(size);
	ui->strokeSizeLabel->setText(labelString);
}

void SpriteEditorVC::setCustomCursor(char const *path)
{
	QPixmap cursor = QPixmap(path).scaled(16,16);
	ui->mainCanvas->setCursor(QCursor(cursor,0,16));
}
