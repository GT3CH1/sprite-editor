#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QDragMoveEvent>

class RenderArea : public QLabel
{
	Q_OBJECT

private:
	QPixmap toRender;

	// How big our pixel is
	int pixelSize = 16;
	// How big our canvas size is.
	int canvasSize = 0;
	// Whether or not the grid is going to shown.
	bool gridShown = true;

	int getNumColsAndRows();
	void drawGrid();
private slots:
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
public:
	RenderArea(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags(), int canvasSize = 512);
public slots:
	void setImage(QPixmap mapToRender);
	void setGridShown(bool gridShown);
signals:
	void clicked();
};

#endif // RENDERAREA_H
