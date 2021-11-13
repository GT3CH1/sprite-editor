#include "renderarea.h"

/**
 * Jonathan Vielstich
 * 11/10/21
 *
 * @brief Displays a clickable QImage and provides a simple
 * method to update that image. To add a RenderArea to an
 * existing form, either add a QLabel to the form and promote
 * it to a RenderArea, or use the addWidget method to add a
 * RenderArea to an existing layout.
 */

/**
 * @brief Constructs a new RenderArea widget
 * @param parent
 */
RenderArea::RenderArea(QWidget* parent,[[maybe_unused]] Qt::WindowFlags f) : QLabel(parent)
{

}

/**
 * @brief Sets the image to be rendered
 * @param toRender - a pointer to the QImage to be displayed
 */
void RenderArea::setImage(QImage* toRender)
{
	this->toRender = toRender;
	setPixmap(QPixmap::fromImage(*toRender));
}

/**
 * @brief Emits a signal that the RenderArea was clicked on
 * @param event
 */
void RenderArea::mousePressEvent([[maybe_unused]] QMouseEvent *event)
{
	emit clicked();
}
