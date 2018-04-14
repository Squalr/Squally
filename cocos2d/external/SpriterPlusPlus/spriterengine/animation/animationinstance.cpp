#include "animationinstance.h"

#include "../global/settings.h"

#include "../timeline/timelineinstance.h"

#include "animation.h"

namespace SpriterEngine
{

	AnimationInstance::AnimationInstance(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, Animation *animation) :
		time(0)
	{
		animation->setupAnimationInstance(entityInstance, entityInstanceData, &mainlineKeys, &timelines, &animationLength, &isLooping);
		mainlineKeyIterator = mainlineKeys.begin();
		name = animation->getName();
	}

	AnimationInstance::~AnimationInstance()
	{
		for (auto& it : mainlineKeys)
		{
			delete it;
		}
		for (auto& it : timelines)
		{
			delete it;
		}
	}

	void AnimationInstance::findAndProcessKeys(real newTime, bool forward, ObjectInterfaceVector **instanceZOrder)
	{
		findCurrentKeys(newTime, forward);
		processCurrentKeys(time, instanceZOrder);
	}

	void AnimationInstance::findCurrentKeys(real newTime, bool forward)
	{
		findCurrentMainlineKey(newTime, forward);
		findCurrentTimelineKeys(time, forward);
	}

	void AnimationInstance::processCurrentKeys(real newTime, ObjectInterfaceVector **instanceZOrder)
	{
		newTime = processCurrentMainlineKey(newTime, instanceZOrder);
		processCurrentTimelineKeys(newTime);
	}

	std::string AnimationInstance::getName()
	{
		return name;
	}

	bool AnimationInstance::looping()
	{
		return isLooping;
	}

	real AnimationInstance::length()
	{
		return animationLength;
	}

	real AnimationInstance::currentTime()
	{
		return time;
	}

	int AnimationInstance::currentMainlineKeyIndex()
	{
		return mainlineKeyIterator - mainlineKeys.begin();
	}

	void AnimationInstance::setCurrentTimeToNextKeyFrame(ObjectInterfaceVector **instanceZOrder)
	{
		int oldIndex = currentMainlineKeyIndex();
		int newIndex = oldIndex + 1;
		if (isLooping)
		{
			while (newIndex >= mainlineKeyCount())
			{
				newIndex -= mainlineKeyCount();
			}
		}

		MainlineKeyInstance *mainKey = mainlineKeyAtIndex(newIndex);
		if (mainKey)
		{
			findAndProcessKeys(mainKey->getTime(), true, instanceZOrder);
		}
	}

	void AnimationInstance::setCurrentTimeToPreviousKeyFrame(ObjectInterfaceVector **instanceZOrder)
	{
		int oldIndex = currentMainlineKeyIndex();
		int newIndex = oldIndex - 1;
		if (isLooping)
		{
			while (newIndex < 0)
			{
				newIndex += mainlineKeyCount();
			}
		}

		MainlineKeyInstance *mainKey = mainlineKeyAtIndex(newIndex);
		if (mainKey)
		{
			findAndProcessKeys(mainKey->getTime(), false, instanceZOrder);
		}
	}

	void AnimationInstance::setCurrentTimeToKeyAtIndex(int newIndex, ObjectInterfaceVector **instanceZOrder)
	{
		MainlineKeyInstance *mainKey = mainlineKeyAtIndex(newIndex);
		if (mainKey)
		{
			findAndProcessKeys(mainKey->getTime(), newIndex > currentMainlineKeyIndex(), instanceZOrder);
		}
	}

	void AnimationInstance::findCurrentTimelineKeys(real newTime, bool forward)
	{
		for (auto& it : timelines)
		{
			it->findCurrentTimelineKey(newTime, forward, animationLength);
		}
	}

	void AnimationInstance::processCurrentTimelineKeys(real newTime)
	{
		for (auto& it : timelines)
		{
			it->processCurrentTimelineKey(newTime);
		}
	}

	void AnimationInstance::blendCurrentTimelineKeys(real newTime, real blendRatio)
	{
		for (auto& it : timelines)
		{
			it->blendCurrentTimelineKey(newTime, blendRatio);
		}
	}

	int AnimationInstance::mainlineKeyCount()
	{
		return mainlineKeys.size();
	}

	void AnimationInstance::findCurrentMainlineKey(real newTime, bool forward)
	{
		while (newTime > animationLength)
		{
			newTime -= animationLength;
		}
		while (newTime < 0)
		{
			newTime += animationLength;
		}
		time = newTime;
		if (forward)
		{
			findMainlineKeyTimeForward(newTime);
		}
		else
		{
			findMainlineKeyTimeBackward(newTime);
		}
	}

	real AnimationInstance::processCurrentMainlineKey(real newTime, ObjectInterfaceVector **instanceZOrder)
	{
		return (*mainlineKeyIterator)->process(newTime, instanceZOrder);
	}

	real AnimationInstance::processRefKeys(real newTime)
	{
		return (*mainlineKeyIterator)->processRefKeys(newTime);
	}

	void AnimationInstance::blendRefKeys(real newTime, real blendRatio)
	{
		return (*mainlineKeyIterator)->blendRefKeys(newTime, blendRatio);
	}

	void AnimationInstance::setZOrder(ObjectInterfaceVector ** instanceZOrder)
	{
		(*mainlineKeyIterator)->setZOrder(instanceZOrder);
	}

	void AnimationInstance::processRefTransforms()
	{
		(*mainlineKeyIterator)->processRefTransforms();
	}

	void AnimationInstance::findMainlineKeyTimeForward(real newTime)
	{
		auto& currentIt = mainlineKeyIterator;
		auto endIt = std::prev(mainlineKeys.end());

		// if the time to find is below the current time
		if (newTime<(*currentIt)->getTime())
		{
			// start at the beginning of the timeline regardless of the startingPosition
			// and end at the startingPosition
			currentIt = mainlineKeys.begin();
			endIt = mainlineKeyIterator;
		}

		while (currentIt != endIt)
		{
			if ((*currentIt)->timeInRange(newTime))
			{
				mainlineKeyIterator = currentIt;
				return;
			}

			++currentIt;
		}

		if ((*currentIt)->getTime() <= newTime)
		{
			mainlineKeyIterator = currentIt;
			return;
		}
		else
		{
			Settings::error("findMainlineKeyTimeForward - could not find key at time " + std::to_string(newTime) + " : falling back on first key");
			mainlineKeyIterator = mainlineKeys.begin();
			return;
		}
	}

	void AnimationInstance::findMainlineKeyTimeBackward(real newTime)
	{
		auto& currentIt = mainlineKeyIterator;
		auto endIt = mainlineKeys.begin();

		// if the time to find is above the next time
		if (newTime > (*currentIt)->getNextTime())
		{
			// if the time to find is after the last keyframe
			if (newTime >= mainlineKeys.back()->getTime())
			{
				// then the last keyframe in the timeline is the correct result
				mainlineKeyIterator = --mainlineKeys.end();
				return;
			}
			else
			{
				// if not, start at the end of the timeline regardless of the startingPosition
				// and end at the startingPosition
				currentIt = --mainlineKeys.end();
			}
		}

		while (currentIt != endIt)
		{
			if ((*currentIt)->timeInRange(newTime))
			{
				mainlineKeyIterator = currentIt;
				return;
			}
			--currentIt; //increment both;
		}
		if ((*currentIt)->getTime() <= newTime)
		{
			mainlineKeyIterator = currentIt;
			return;
		}
		else
		{
			mainlineKeyIterator = mainlineKeys.begin();
			Settings::error("AnimationInstance::findMainlineKeyTimeBackward - could not find key at time " + std::to_string(newTime) + " : falling back on first key");
			return;
		}
	}

	MainlineKeyInstance * AnimationInstance::mainlineKeyAtIndex(int index)
	{
		if (index >= 0 && index < mainlineKeys.size())
		{
			return mainlineKeys.at(index);
		}
		else
		{
			return 0;
		}
	}

}
