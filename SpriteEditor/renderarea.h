#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QLabel>

class RenderArea : public QLabel
{
	Q_OBJECT

private:
	QImage* toRender;
private slots:
	void mousePressEvent(QMouseEvent*);
public:
	RenderArea(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
public slots:
	void setImage(QImage*);
signals:
	void clicked();
};

#endif // RENDERAREA_H
