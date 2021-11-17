#ifndef SPRAYCAN_H
#define SPRAYCAN_H

#include "itool.h"
#include "istencilgenerator.h"

class SprayCan : public ITool
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
	SprayCan(IStencilGenerator* generator);
	SprayCan(const SprayCan& other);
	SprayCan& operator=(SprayCan otherCopy);
	virtual ~SprayCan();
	virtual void apply(ActionState& canvasState, const CallbackOptions& callbacks);
	static QRect ConstrainStencilBounds(Pointer2DArray<float> stencil, int stencilCenterX, int stencilCenterY, int areaWidth, int areaHeight,  BoundsInformation& outInfo);
private:
	IStencilGenerator* stencilGenerator;
protected:
	Pointer2DArray<float> stencil;
	void setStencilOnSizeChange(unsigned int newSize);
};

#endif // SPRAYCAN_H
