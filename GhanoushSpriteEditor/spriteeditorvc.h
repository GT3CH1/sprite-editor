#ifndef SPRITEEDITORVC_H
#define SPRITEEDITORVC_H

#include <QAction>
#include <QColorDialog>
#include <QDir>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QPushButton>
#include <QScrollArea>
#include <QSlider>
#include <QTimer>

#include "renderarea.h"
#include "spriteeditormodel.h"
#include "imagesizedialog.h"
#include "ui_spriteeditorvc.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class SpriteEditorVC;
}
QT_END_NAMESPACE

class SpriteEditorVC : public QMainWindow
{
	Q_OBJECT
private:
	const char *FILE_FILTER = "Sprite Files (*.ssp);;All Files (*.*)";
	// FPS Slider parameters
	const int FPS_INTERVAL = 10;
	const int FPS_MAX = 60;
	const int FPS_STEP = 10;
	// Frame scaling
	const int PREVIEW_SIZE = 128;	// Animation playback
	const int FRAME_SIZE = 64;		// Frame display
	// Default colors
	const int RED = 9;
	const int ORANGE = 21;
	const int YELLOW = 45;
	const int GREEN = 36;
	const int PURPLE = 7;
	const int BLUE = 5;
	const int BLACK = 0;
	const int WHITE = 47;
	// Icon file paths
	const char* INVERT_SVG_PATH = ":/res/invert.svg";
	const char* RAINBOW_SVG_PATH = ":/res/rainbow.svg";
	const char* SOFT_ERASER_PATH = ":/res/soft-eraser.svg";
	const char* PEN_SVG_PATH = ":/res/pen.svg";
	const char* ERASER_SVG_PATH = ":/res/eraser.svg";
	const char* SOFT_BRUSH_PATH = ":/res/soft-brush.svg";
	const char* SPRAY_CAN_SVG_PATH = ":/res/spray-can.svg";
	const char* BLUR_SVG_PATH = ":/res/blur.svg";
	const char* GRID_SVG_PATH = ":/res/grid.svg";
	const char* SAVE_SVG_PATH = ":/res/save.svg";
	const char* OPEN_SVG_PATH = ":/res/open.svg";
	const char* CLOSE_SVG_PATH = ":/res/close.svg";
	const char* NEW_SVG_PATH = ":/res/new.svg";

	SpriteEditorModel *model;	// Drawing model
	Ui::SpriteEditorVC *ui;		// UI
	QHBoxLayout *framePreviewLayout;	// Horizontal layout for frame previews
	int indexOfActiveFrame = 0;	// Tracks the active frame
	int indexOfPlayback = 0;	// Tracks the current animation frame
	int fps = 0;				// Tracks the FPS of the animation
	QTimer playbackUpdater;		// Triggers a frame change in the animation
	QString path = QDir::homePath();	// Path to the directory of the last file accessed, defaults to user's home directory
	std::vector<RenderArea *> framePreviews; // Tracks the frames displayed in the scroll area
	// UI button actions
	QAction *saveAction;
	QAction *openAction;
	QAction *newFileAction;
	QAction *rainbowBrushSelected;
	QAction *softEraserSelected;
	QAction *invertSelected;
	QAction *hardPenSelected;
	QAction *softBrushSelected;
	QAction *hardEraserSelected;
	QAction *sprayCanSelected;
	QAction *gaussianSelected;
	QAction *gridSelected;
	QAction *rainbowSpraycanSelected;
	// UI Elements
	ImageSizeDialog imageSizeDialogue;
	QColorDialog *colorDialog;
	QMenu *fileMenu;
	QMenu *toolsMenu;

	void setButtonColor(QPushButton *button, QString hex);
	void createMenu();
	void setupButtonColors();
	void setCustomCursor(char const *path);
	void changeActiveColor(QPushButton *);

private slots:
	void deleteFrame();
	void addFrame();
	void previewFrames();
	void updatePlaybackFrame();
	void on_fpsSlider_valueChanged(int);
	void keyPressEvent(QKeyEvent *);
	void savePressed();
	void loadPressed();
	void on_nextFrameButton_clicked();
	void on_lastFrameButton_clicked();
	void updateActiveFrame(int);
	void updateActivePreview(int);
	void startSizeDialogue();
	void finishSizeDialogue(int size);
	void changeFocus();

public:
	SpriteEditorVC(QWidget *parent = nullptr);
	~SpriteEditorVC();

public slots:
	void showColorDialog();
	void updateCustomButtonColors();
	void colorButtonClicked();
	void setInvertBrush();
	void setRainbowBrush();
	void setSoftEraser();
	void setHardPen();
	void setSoftBrush();
	void setHardEraser();
	void setSprayCan();
	void setGaussian();
	void setRainbowSpraycan();
	void setBrushSizeLabel(int size);



signals:
	void colorChanged(QColor color);
	void updateTool(SpriteEditorModel::ToolType toolType);
	void incrementToolSize();
	void decrementToolSize();
	void setActiveColor(QColor);
	void changeActiveFrame(int);
	void changeActiveTool(SpriteEditorModel::ToolType);
	void add();
	void remove(int);
	void save(std::string, std::string);
	void load(std::string, std::string);
	void toggleGrid();
	void duplicateFrame();
	void clearFrame();
	void addNewFrame();
	void deleteActiveFrame(int);
};
#endif // SPRITEEDITORVC_H
