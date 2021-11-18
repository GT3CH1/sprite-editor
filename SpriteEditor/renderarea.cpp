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
RenderArea::RenderArea(QWidget *parent, [[maybe_unused]] Qt::WindowFlags f, int canvasSize) : QLabel(parent), canvasSize(canvasSize)
{
	QPixmap blank(canvasSize, canvasSize);
	blank.fill();
	setImage(blank);
}

/**
 * @brief Gets the maximum number of columns and rows that we can draw on.
 */
int RenderArea::getNumColsAndRows()
{
	return 512 / canvasSize;
}

/**
 * @brief Sets the image to be rendered
 * @param toRender - a pointer to the QImage to be displayed
 */
void RenderArea::setImage(QPixmap newMapToRender)
{
	setImageScaled(newMapToRender, 512);
}

/**
 * @brief Sets the image to be rendered
 * @param toRender - a pointer to the QImage to be displayed
 * @param scale - The scale in which to show the image at.
 */
void RenderArea::setImageScaled(QPixmap newMapToRender, int scale)
{
	QPixmap newMap(newMapToRender.scaled(scale, scale, Qt::KeepAspectRatioByExpanding));
	gridRender = newMap;
	QPainter paint(&gridRender);
	paint.setPen(Qt::gray);

	for (int loc = 1; loc < canvasSize + 2; loc++)
	{
		paint.drawLine(loc * (512 / canvasSize), 0, loc * (512 / canvasSize), 512);
		paint.drawLine(0, loc * (512 / canvasSize), 512, loc * (512 / canvasSize));
	}

	paint.end();

	if (gridShown)
		setPixmap(gridRender);

	else
		setPixmap(newMap);

	toRender = newMap;
	update();
	toRender = newMap.scaled(canvasSize, canvasSize, Qt::KeepAspectRatioByExpanding);
}

/**
 * @brief Emits a signal that the RenderArea was clicked on
 * @param event
 */
void RenderArea::mousePressEvent(QMouseEvent *evt)
{
	int x = evt->pos().x();
	unsigned int y = evt->pos().y();

	if (x < 512 && y < 512)
		emit clicked((float)x / 512.0, (float)y / 512.0);
}

/**
 * @brief Handles the mouse being moved across the RenderArea
 * @param evt
 */
void RenderArea::mouseMoveEvent(QMouseEvent *evt)
{
	if (evt->buttons() & Qt::LeftButton)
	{
		int x = evt->pos().x();
		int y = evt->pos().y();

		if ((x < 510 && x > 2) && (y < 510 && y > 2))
			emit clicked((float)x / 512.0, (float)y / 512.0);
	}
}

/**
 * @brief Handles the mouse being released.
 * @param evt
 */
void RenderArea::mouseReleaseEvent(QMouseEvent *evt)
{
	int x = evt->pos().x();
	unsigned int y = evt->pos().y();

	if (x < 512 && y < 512)
		emit released((float)x / 512.0, (float)y / 512.0);
}

/**
 * @brief Sets whether or not the grid is shown.
 * @param gridShown - When true, the grid will be shown. If false, the grid will not be showed.
 */
void RenderArea::toggleGrid()
{
	this->gridShown = !gridShown;
	setImage(toRender);
}

/**
 * @brief Updates the canvas size to match the given size.
 * @param size - The new canvas size.
 */
void RenderArea::setCanvasSize(int size)
{
	canvasSize = size;
	setImage(toRender);
}
