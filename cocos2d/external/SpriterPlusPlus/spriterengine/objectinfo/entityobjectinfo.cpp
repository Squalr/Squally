#include "entityobjectinfo.h"

namespace SpriterEngine
{

	EntityObjectInfo::EntityObjectInfo() :
		scale(1, 1),
		alpha(1),
		timeRatio(0)
	{
	}

	point EntityObjectInfo::getPosition()
	{
		return position;
	}

	real EntityObjectInfo::getAngle()
	{
		return angle.angle;
	}

	point EntityObjectInfo::getScale()
	{
		return scale;
	}

	real EntityObjectInfo::getAlpha()
	{
		return alpha;
	}

	real EntityObjectInfo::getTimeRatio()
	{
		return timeRatio;
	}


	void EntityObjectInfo::setPosition(const point &newPosition)
	{
		position = newPosition;
	}

	void EntityObjectInfo::setAngle(real newAngle)
	{
		angle.angle = newAngle;
	}

	void EntityObjectInfo::setScale(const point &newScale)
	{
		scale = newScale;
	}

	void EntityObjectInfo::setAlpha(real newAlpha)
	{
		alpha = newAlpha;
	}

	void EntityObjectInfo::setSpin(int newSpin)
	{
		angle.spinDirection = newSpin;
	}

	void EntityObjectInfo::setTimeRatio(real newCurrentTimeRatio)
	{
		timeRatio = newCurrentTimeRatio;
	}


	void EntityObjectInfo::setObjectToLinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject)
	{
		resultObject->setAngle(angle.angleLinear(bObject->getAngle(), t));
		resultObject->setPosition(linear(position, bObject->getPosition(), t));
		resultObject->setScale(linear(scale, bObject->getScale(), t));
		resultObject->setAlpha(linear(alpha, bObject->getAlpha(), t));
		resultObject->setTimeRatio(linear(timeRatio, bObject->getTimeRatio(), t));
	}

}
