#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QDragMoveEvent>
#include <QPoint>

class RenderArea : public QLabel
{
	Q_OBJECT

private:
	QPixmap toRender;
	QPixmap gridRender;
	int canvasSize = 0;
	bool gridShown = false;
	int getNumColsAndRows();
	QPoint lastPosition;
private slots:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
public:
	RenderArea(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags(), int canvasSize = 64);
public slots:
	void setImage(QPixmap mapToRender);
	void setImageScaled(QPixmap mapToRender, int scale);
	void toggleGrid();
	void setCanvasSize(int size);
signals:
	void clicked(float x, float y);
	void released(float x, float y);
	void pressed();
};

#endif // RENDERAREA_H
