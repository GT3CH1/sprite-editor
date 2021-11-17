#include "renderarea.h"

/**
 * Draws a single frame from the sprite
 * Jonathan Vielstich
 * Gavin Pease
 * 11/10/21
 *
 * @brief Displays a clickable QPixMap and provides a simple
 * method to update that image. To add a RenderArea to an
 * existing form, either add a QLabel to the form and promote
 * it to a RenderArea, or use the addWidget method to add a
 * RenderArea to an existing layout.
 */

/**
 * @brief Constructs a new RenderArea widget
 * @param parent
 */
RenderArea::RenderArea(QWidget* parent,[[maybe_unused]] Qt::WindowFlags f, int canvasSize) : QLabel(parent), canvasSize(canvasSize)
{
	QPixmap blank(canvasSize,canvasSize);
	blank.fill();
	setImage(blank);
	drawGrid(blank);
}

/**
 * @brief Gets the maximum number of columns and rows that we can draw on.
 */
int RenderArea::getNumColsAndRows(){
	return 512/canvasSize;
}

/**
 * @brief Sets the image to be rendered
 * @param toRender - a pointer to the QImage to be displayed
 */
void RenderArea::setImage(QPixmap newMapToRender)
{
	QPixmap newMap(newMapToRender.scaled(512,512,Qt::KeepAspectRatioByExpanding));
	QPainter paint(&newMap);
	if(gridShown)
		paint.setPen(Qt::black);
	else
		paint.setPen(Qt::white);
	for(int loc = 0; loc < canvasSize; loc++){
		paint.drawLine(loc*(512/canvasSize),0,loc*(512/canvasSize),512);
		paint.drawLine(0,loc*(512/canvasSize),512,loc*(512/canvasSize));
	}
	paint.end();
	setPixmap(newMap);
	toRender = newMap;

	update();
	toRender = newMap.scaled(canvasSize,canvasSize,Qt::KeepAspectRatioByExpanding);
}

/**
 * @brief Emits a signal that the RenderArea was clicked on
 * @param event
 */
void RenderArea::mousePressEvent(QMouseEvent *evt)
{
		int x = evt->pos().x();
		unsigned int y = evt->pos().y();
		if((x < 512 && x > 0) && (y < 512 && y > 0))
			emit clicked((float)x/512.0,(float)y/512.0);
		drawGrid(toRender);
}

/**
 * @brief Handles the mouse being moved across the RenderArea
 * @param evt
 */
void RenderArea::mouseMoveEvent(QMouseEvent *evt)
{
	if(evt->buttons() & Qt::LeftButton)
	{
		int x = evt->pos().x();
		int y = evt->pos().y();
		/*if((x < 510 && x > 2) && (y < 510 && y > 2))
			emit clicked((float)x/512.0,(float)y/512.0); */
	}
}

/**
 * @brief Draws a grid on the render area
 */
void RenderArea::drawGrid(QPixmap newFrame){
	qDebug() << "Grid size: " << newFrame.size();
}

/**
 * @brief Sets whether or not the grid is shown.
 * @param gridShown - When true, the grid will be shown. If false, the grid will not be showed.
 */
void RenderArea::setGridShown(bool gridShown){
	this->gridShown = gridShown;
	drawGrid(toRender);
}

int RenderArea::getPixelSize(){
		qDebug() << "Pixel size: " << (512/canvasSize);
		return (512/canvasSize);
}
