#ifndef ITOOL_H
#define ITOOL_H

#include "actionstate.h"
#include "callbackoptions.h"

/**
 * Kenzie Evans
 *
 * 11/13/2021
 *
 * @brief The ITool class applies the data from the action state
 * and callback information to the current active frame.
 */

class ITool
{
public:
	virtual void apply(ActionState& canvasState, const CallbackOptions& callbacks) = 0;
	virtual ~ITool(){}
};

#endif // ITOOL_H
