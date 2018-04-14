#include "triggerobjectinfo.h"

namespace SpriterEngine
{

	TriggerObjectInfo::TriggerObjectInfo() :
		triggerCount(0)
	{
	}

	int TriggerObjectInfo::getTriggerCount()
	{
		return triggerCount;
	}

	void TriggerObjectInfo::setTriggerCount(int newTriggerCount)
	{
		triggerCount = newTriggerCount;
	}

	void TriggerObjectInfo::setToBlendedLinear(UniversalObjectInterface *aObject, UniversalObjectInterface *bObject, real t, real blendRatio, ObjectRefInstance *blendedRefInstance)
	{
	}

}
