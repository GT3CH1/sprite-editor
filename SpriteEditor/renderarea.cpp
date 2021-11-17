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
	return 512/canvasSize;
}

/**
 * @brief Sets the image to be rendered
 * @param toRender - a pointer to the QImage to be displayed
 */
void RenderArea::setImage(QPixmap newMapToRender)
{
	QPixmap newMap(newMapToRender.scaled(512,512,Qt::KeepAspectRatio));
	setPixmap(newMap);
	toRender = newMap;
	update();
	repaint();
}

/**
 * @brief Emits a signal that the RenderArea was clicked on
 * @param event
 */
void RenderArea::mousePressEvent(QMouseEvent *evt)
{
		int x = evt->pos().x();
		unsigned int y = evt->pos().y();
		emit clicked(x/512,y/512);
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
		emit clicked(x/512,y/512);
	}
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
		paint.drawLine(loc*getPixelSize(),0,loc*getPixelSize(),canvasSize*512);
		paint.drawLine(0,loc*getPixelSize(),canvasSize*512,loc*getPixelSize());
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

int RenderArea::getPixelSize(){
		return (512/canvasSize);
}
