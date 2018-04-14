#include "mainlinekey.h"

#include "../global/settings.h"

#include "../timeinfo/timeinfo.h"
#include "../objectref/objectref.h"
#include "../entity/entityinstance.h"

namespace SpriterEngine
{

	MainlineKey::MainlineKey(TimeInfo *initialTimeInfo) :
		timeInfo(initialTimeInfo)
	{
	}

	MainlineKey::~MainlineKey()
	{
		delete timeInfo;

		for (auto& it : boneRefs)
		{
			delete it;
		}

		for (auto& it : zOrderRefs)
		{
			delete it;
		}
	}

	void MainlineKey::setupRefInstancesAndTimeInfo(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, RefInstanceVector *refInstances, ObjectInterfaceVector *instanceZOrder, TimeInfo *&instanceTimeInfo)
	{
		for (auto& it : boneRefs)
		{
			refInstances->push_back(it->getNewObjectRefInstance(entityInstance, entityInstanceData));
		}
		for (auto& it : zOrderRefs)
		{
			refInstances->push_back(it->getNewObjectRefInstance(entityInstance, entityInstanceData));
			instanceZOrder->push_back(entityInstanceData->getObjectInstance(it->id()));
		}
		if (Settings::enableDebugBones)
		{
			for (auto& it : boneRefs)
			{
				instanceZOrder->push_back(entityInstanceData->getObjectInstance(it->id()));
			}
		}
		instanceTimeInfo = timeInfo;
	}

	void MainlineKey::pushBackBoneRef(ObjectRef *ref)
	{
		boneRefs.push_back(ref);
	}

	void MainlineKey::pushBackZOrderRef(ObjectRef *ref)
	{
		zOrderRefs.push_back(ref);
	}

	real MainlineKey::getTime()
	{
		return timeInfo->getTime();
	}

}
