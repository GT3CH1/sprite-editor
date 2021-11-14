#ifndef ITOOL_H
#define ITOOL_H

#include "actionstate.h"
#include "callbackoptions.h"

class ITool
{
public:
	virtual void apply(const ActionState& canvasState, const CallbackOptions& callbacks) = 0;
	virtual ~ITool() = 0;
};

#endif // ITOOL_H
