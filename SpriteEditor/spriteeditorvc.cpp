#include "spriteeditorvc.h"
#include "ui_spriteeditorvc.h"

SpriteEditorVC::SpriteEditorVC(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::SpriteEditorVC)
{
	ui->setupUi(this);
    this->setStyleSheet(QString("QMainWindow { background-color:white}"));
    // Set up FPS slider.
	ui->fpsSlider->setTickInterval(FPS_INTERVAL);
	ui->fpsSlider->setSingleStep(FPS_STEP);
	ui->fpsSlider->setMaximum(FPS_MAX);
	qDebug() << ui->primaryColorButton1->styleSheet();

	QObject::connect(&this->playbackUpdater, &QTimer::timeout, this, &SpriteEditorVC::updatePreview);
}

SpriteEditorVC::~SpriteEditorVC()
{
	delete ui;
}

/**
 * @brief Advances the animation playback frame
 */
void SpriteEditorVC::updatePreview()
{
	//TODO(JVielstich): get frame from model

	//TODO(JVielstich): set playback frame
}

/**
 * @brief Updates the FPS label and controls the animation
 * playback timer
 * @param value
 */
void SpriteEditorVC::on_fpsSlider_valueChanged(int value)
{
    ui->fpsLabel->setText(QString::number(value));
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
	default:
		// do nothing
		break;
	}
}

/**
 * @brief Changes the active color to that of Color Button 1
 */
void SpriteEditorVC::on_primaryColorButton1_clicked()
{
	emit setActiveColor(ui->primaryColorButton1->palette().color(QWidget::backgroundRole()));
}

/**
 * @brief Changes the active color to that of Color Button 2
 */
void SpriteEditorVC::on_primaryColorButton2_clicked()
{
	emit setActiveColor(ui->primaryColorButton2->palette().color(QWidget::backgroundRole()));
}

/**
 * @brief Changes the active color to that of Color Button 3
 */
void SpriteEditorVC::on_primaryColorButton3_clicked()
{
	emit setActiveColor(ui->primaryColorButton3->palette().color(QWidget::backgroundRole()));
}

/**
 * @brief Changes the active color to that of Color Button 4
 */
void SpriteEditorVC::on_primaryColorButton4_clicked()
{
	emit setActiveColor(ui->primaryColorButton4->palette().color(QWidget::backgroundRole()));
}

/**
 * @brief Changes the active color to that of Color Button 5
 */
void SpriteEditorVC::on_primaryColorButton5_clicked()
{
	emit setActiveColor(ui->primaryColorButton5->palette().color(QWidget::backgroundRole()));
}


/**
 * @brief Changes the active color to that of Color Button 6
 */
void SpriteEditorVC::on_primaryColorButton6_clicked()
{
	emit setActiveColor(ui->primaryColorButton6->palette().color(QWidget::backgroundRole()));
}

/**
 * @brief Changes the active color to that of Color Button 7
 */
void SpriteEditorVC::on_primaryColorButton7_clicked()
{
	emit setActiveColor(ui->primaryColorButton7->palette().color(QWidget::backgroundRole()));
}

/**
 * @brief Changes the active color to that of Color Button 8
 */
void SpriteEditorVC::on_primaryColorButton8_clicked()
{
	emit setActiveColor(ui->primaryColorButton8->palette().color(QWidget::backgroundRole()));
}

/**
 * @brief Changes the active color to that of Custom Color Button 1
 */
void SpriteEditorVC::on_customColorButton1_clicked()
{
	emit setActiveColor(ui->customColorButton1->palette().color(QWidget::backgroundRole()));
}

/**
 * @brief Changes the active color to that of Custom Color Button 2
 */
void SpriteEditorVC::on_customColorButton2_clicked()
{
	emit setActiveColor(ui->customColorButton2->palette().color(QWidget::backgroundRole()));
}

/**
 * @brief Changes the active color to that of Custom Color Button 3
 */
void SpriteEditorVC::on_customColorButton3_clicked()
{
	emit setActiveColor(ui->customColorButton3->palette().color(QWidget::backgroundRole()));
}

/**
 * @brief Changes the active color to that of Custom Color Button 4
 */
void SpriteEditorVC::on_customColorButton4_clicked()
{
	emit setActiveColor(ui->customColorButton4->palette().color(QWidget::backgroundRole()));
}

/**
 * @brief Changes the active color to that of Custom Color Button 5
 */
void SpriteEditorVC::on_customColorButton5_clicked()
{
	emit setActiveColor(ui->customColorButton5->palette().color(QWidget::backgroundRole()));
}

/**
 * @brief Changes the active color to that of Custom Color Button 6
 */
void SpriteEditorVC::on_customColorButton6_clicked()
{
	emit setActiveColor(ui->customColorButton6->palette().color(QWidget::backgroundRole()));
}

/**
 * @brief Changes the active color to that of Custom Color Button 7
 */
void SpriteEditorVC::on_customColorButton7_clicked()
{
	emit setActiveColor(ui->customColorButton7->palette().color(QWidget::backgroundRole()));
}

/**
 * @brief Changes the active color to that of Custom Color Button 8
 */
void SpriteEditorVC::on_customColorButton8_clicked()
{
	emit setActiveColor(ui->customColorButton8->palette().color(QWidget::backgroundRole()));
}


void SpriteEditorVC::on_penToolButton_clicked()
{
	//TODO(JVielstich): Emit change tool signal
}


void SpriteEditorVC::on_brushToolButton_clicked()
{
	//TODO(JVielstich): Emit change tool signal
}


void SpriteEditorVC::on_eraserToolButton_clicked()
{
	//TODO(JVielstich): Emit change tool signal
}


void SpriteEditorVC::on_toolButton4_clicked()
{
	//TODO(JVielstich): Emit change tool signal
}

