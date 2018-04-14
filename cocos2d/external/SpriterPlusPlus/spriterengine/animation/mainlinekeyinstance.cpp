#include "mainlinekeyinstance.h"

#include "../timeinfo/timeinfo.h"
#include "../objectref/objectrefinstance.h"

#include "mainlinekey.h"

namespace SpriterEngine
{

	MainlineKeyInstance::MainlineKeyInstance(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, MainlineKey *mainlineKey)
	{
		mainlineKey->setupRefInstancesAndTimeInfo(entityInstance, entityInstanceData, &refs, &zOrder, timeInfo);
	}

	MainlineKeyInstance::~MainlineKeyInstance()
	{
		for (auto& it : refs)
		{
			delete it;
		}
	}

	real MainlineKeyInstance::process(real currentTime, ObjectInterfaceVector **instanceZOrder)
	{
		currentTime = timeInfo->getEasedTime(currentTime);
		for (auto& it : refs)
		{
			it->process(currentTime);
		}
		*instanceZOrder = &zOrder;
		return currentTime;
	}

	real MainlineKeyInstance::processRefKeys(real currentTime)
	{
		currentTime = timeInfo->getEasedTime(currentTime);
		for (auto& it : refs)
		{
			it->preProcess();
			it->processKey(currentTime);
		}
		return currentTime;
	}

	void MainlineKeyInstance::blendRefKeys(real currentTime, real blendRatio)
	{
		currentTime = timeInfo->getEasedTime(currentTime);
		for (auto& it : refs)
		{
			it->blendKey(currentTime, blendRatio);
		}
	}

	void MainlineKeyInstance::setZOrder(ObjectInterfaceVector **instanceZOrder)
	{
		*instanceZOrder = &zOrder;
	}

	void MainlineKeyInstance::processRefTransforms()
	{
		for (auto& it : refs)
		{
			it->processTransform();
		}
	}

	real MainlineKeyInstance::getTime()
	{
		return timeInfo->getTime();
	}

	real MainlineKeyInstance::getNextTime()
	{
		return timeInfo->getNextTime();
	}

	bool MainlineKeyInstance::timeInRange(real timeToCheck)
	{
		return timeInfo->timeInRange(timeToCheck);
	}

}
