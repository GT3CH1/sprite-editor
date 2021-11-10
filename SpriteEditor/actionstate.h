#ifndef ACTIONSTATE_H
#define ACTIONSTATE_H

#include <QColor>
#include <QImage>

class ActionState
{
public:
	const int ToolState;
	const QColor ToolColor;
	const int MouseXGridCoord;
	const int MouseYGridCoord;
	const QImage& ActiveLayer;
	ActionState(const int state, const QColor color, const int x,
				const int y, const QImage& layer);
};

#endif // ACTIONSTATE_H
