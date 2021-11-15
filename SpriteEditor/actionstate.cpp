/**
 * Kenzie Evans
 * 11/10/21
 *
 * @brief A struct that holds the size of a tool, the color of a tool, the x and y
 * coordinate of the mouse and the active layer.
*/

#include "actionstate.h"

ActionState::ActionState(const int size, const QColor color, const int x,
						 const int y, QPixmap frame)
	: TOOL_SIZE(size), TOOL_COLOR(color), MOUSE_X_GRID_COORD(x), MOUSE_Y_GRID_COORD(y), ACTIVE_FRAME(frame)
{	
}
