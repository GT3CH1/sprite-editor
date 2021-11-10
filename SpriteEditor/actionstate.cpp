/*
 * A struct that holds the state of a tool, the color of a tool, the x and y
 * coordinate of the mouse and the active layer.
 *
 * Author: Kenzie Evans
 * Date Created: 11/10/21
*/

#include "actionstate.h"

ActionState::ActionState(const int state, const QColor color, const int x,
						 const int y, const QImage& layer)
	: ToolState(state), ToolColor(color), MouseXGridCoord(x), MouseYGridCoord(y), ActiveLayer(layer)
{	
}
