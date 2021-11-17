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
    QPixmap gridRender;
	// How big our canvas size is.
	int canvasSize = 0;
	// Whether or not the grid is going to shown.
	bool gridShown = true;
	int getNumColsAndRows();
private slots:
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
public:
	RenderArea(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags(), int canvasSize = 64);
	int getPixelSize();
public slots:
	void setImage(QPixmap mapToRender);
	void toggleGrid();
signals:
	void clicked(float x, float y);
};

#endif // RENDERAREA_H
