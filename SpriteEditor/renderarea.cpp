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
	drawGrid();
}

/**
 * @brief Gets the maximum number of columns and rows that we can draw on.
 */
int RenderArea::getNumColsAndRows(){
	return canvasSize/pixelSize;
}

/**
 * @brief Sets the image to be rendered
 * @param toRender - a pointer to the QImage to be displayed
 */
void RenderArea::setImage(QPixmap newMapToRender)
{
	toRender = newMapToRender;;
	setPixmap(toRender);
	update();
	repaint();
}

/**
 * @brief Emits a signal that the RenderArea was clicked on
 * @param event
 */
void RenderArea::mousePressEvent(QMouseEvent *evt)
{
	QPainter paint(&toRender);
	paint.setPen(QColor(0, 0, 0, 255));
	int col = evt->position().x()/pixelSize;
	int row = evt->position().y()/pixelSize;
	paint.fillRect(col*pixelSize,row*pixelSize,pixelSize,pixelSize,Qt::blue);
	paint.end();
	setImage(toRender);
}

/**
 * @brief Draws a grid on the render area
 */
void RenderArea::drawGrid(){
	QPainter paint(&toRender);
	if(gridShown)
		paint.setPen(Qt::black);
	else
		paint.setPen(Qt::white);
	for(int loc = 1; loc < getNumColsAndRows(); loc++){
		paint.drawLine(loc*pixelSize,0,loc*pixelSize,canvasSize);
		paint.drawLine(0,loc*pixelSize,canvasSize,loc*pixelSize);
	}
	paint.end();
	setImage(toRender);
}

/**
 * @brief Sets whether or not the grid is shown.
 * @param gridShown - When true, the grid will be shown. If false, the grid will not be showed.
 */
void RenderArea::setGridShown(bool gridShown){
	this->gridShown = gridShown;
	drawGrid();
}
