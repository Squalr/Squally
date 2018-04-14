#include "boneobjectinfo.h"

namespace SpriterEngine
{

	BoneObjectInfo::BoneObjectInfo() :
		scale(1, 1),
		alpha(1)
	{
	}

	point BoneObjectInfo::getPosition()
	{
		return position;
	}

	real BoneObjectInfo::getAngle()
	{
		return angle.angle;
	}

	point BoneObjectInfo::getScale()
	{
		return scale;
	}

	real BoneObjectInfo::getAlpha()
	{
		return alpha;
	}


	void BoneObjectInfo::setPosition(const point &newPosition)
	{
		position = newPosition;
	}

	void BoneObjectInfo::setAngle(real newAngle)
	{
		angle.angle = newAngle;
	}

	void BoneObjectInfo::setScale(const point &newScale)
	{
		scale = newScale;
	}

	void BoneObjectInfo::setAlpha(real newAlpha)
	{
		alpha = newAlpha;
	}

	void BoneObjectInfo::setSpin(int newSpin)
	{
		angle.spinDirection = newSpin;
	}

	void BoneObjectInfo::setObjectToLinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject)
	{
		resultObject->setAngle(angle.angleLinear(bObject->getAngle(), t));
		resultObject->setPosition(linear(position, bObject->getPosition(), t));
		resultObject->setScale(linear(scale, bObject->getScale(), t));
		resultObject->setAlpha(linear(alpha, bObject->getAlpha(), t));
	}

}
