#ifndef ACTIONSTATE_H
#define ACTIONSTATE_H

#include <QColor>
#include <QPixmap>

class ActionState
{
public:
	const int TOOL_SIZE;
	const QColor TOOL_COLOR;
	const int MOUSE_X_GRID_COORD;
	const int MOUSE_Y_GRID_COORD;
	QPixmap ACTIVE_FRAME;
	ActionState(const int size, const QColor color, const int x,
				const int y, QPixmap frame);
};

#endif // ACTIONSTATE_H
