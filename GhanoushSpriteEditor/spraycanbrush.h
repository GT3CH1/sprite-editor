#ifndef SprayCanBrushBRUSH_H
#define SprayCanBrushBRUSH_H

#include "itool.h"
#include "istencilgenerator.h"

class SprayCanBrush : public ITool
{
protected:
	struct BoundsInformation
	{
	public:
		/**
		 *  deltaX and deltaY are the position of a bounded area relative
		 *  to the initial area that was bounded.
		 */
		int deltaX = 0;
		int deltaY = 0;
	};

public:
	SprayCanBrush(IStencilGenerator *generator);
	SprayCanBrush(const SprayCanBrush &other);
	SprayCanBrush &operator=(SprayCanBrush otherCopy);
	virtual ~SprayCanBrush();
	virtual void apply(ActionState& canvasState, const CallbackOptions& callbacks);
	static QRect ConstrainStencilBounds(Pointer2DArray<float> stencil, int stencilCenterX, int stencilCenterY, int areaWidth, int areaHeight,  BoundsInformation& outInfo);

protected:
	IStencilGenerator* stencilGenerator;
	Pointer2DArray<float> stencil;
	void setStencilOnSizeChange(unsigned int newSize);
};

#endif // SprayCanBrushBRUSH_H
