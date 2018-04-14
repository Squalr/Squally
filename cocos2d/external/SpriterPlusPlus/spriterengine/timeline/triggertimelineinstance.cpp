#include "triggertimelineinstance.h"

#include "../global/settings.h"

#include "../entity/entityinstancedata.h"
#include "../objectinfo/universalobjectinterface.h"

#include "timeline.h"
#include "timelinekey.h"

namespace SpriterEngine
{

	TriggerTimelineInstance::TriggerTimelineInstance(EntityInstanceData *entityInstanceData, Timeline *timeline, int objectId) :
		TimelineInstance(timeline),
		triggerCount(0),
		previousTime(0)
	{	
		resultObject = entityInstanceData->getTriggerObject(objectId);
	}

	TriggerTimelineInstance::TriggerTimelineInstance(EntityInstanceData * entityInstanceData, Timeline * timeline) :
		TimelineInstance(timeline),
		triggerCount(0),
		previousTime(0)
	{
		resultObject = 0;
	}

	void TriggerTimelineInstance::findCurrentTimelineKey(real newTime, bool forward, real animationLength)
	{
		triggerCount = 0;
		if (forward)
		{
			findTimeForward(newTime, animationLength);
		}
		else
		{
			findTimeBackward(newTime, animationLength);
		}
		previousTime = newTime;
	}

	void TriggerTimelineInstance::processCurrentTimelineKey(real newTime)
	{
		resultObject->setTriggerCount(triggerCount);
	}

	void TriggerTimelineInstance::findTimeForward(real newTime, real animationLength)
	{
		auto& currentIt = timelineKeyIterator;
		auto endIt = std::prev(timelineKeys->end());

		// if the time to find is below the current time
		if (newTime < (*currentIt)->getTime())
		{
			auto& tempIt = timelineKeyIterator;

			findTimeForward(animationLength, animationLength);
			previousTime -= animationLength;

			// start at the beginning of the timeline regardless of the startingPosition
			// and end at the startingPosition
			currentIt = timelineKeys->begin();
			endIt = tempIt;
		}

		real aTime = previousTime;
		real bTime = newTime;

		if (bTime < aTime)
		{
			if (aTime < (*currentIt)->getTime())
			{
				bTime += animationLength;
			}
			else
			{
				aTime -= animationLength;
			}
		}

		while (currentIt != endIt)
		{
			checkTrigger(*currentIt, aTime, bTime);

			if ((*currentIt)->timeInRange(newTime))
			{
				timelineKeyIterator = currentIt;
				return;
			}

			currentIt++;
		}

		if ((*currentIt)->getTime() <= newTime)
		{
			checkTrigger(*currentIt, aTime, bTime);

			timelineKeyIterator = currentIt;
			return;
		}
		else
		{
			Settings::error("TriggerTimelineInstance::findTimeForward - could not find key at time " + std::to_string(newTime) + " : falling back on first key");
			timelineKeyIterator = timelineKeys->begin();
			return;
		}
	}

	void TriggerTimelineInstance::findTimeBackward(real newTime, real animationLength)
	{
		auto& currentIt = timelineKeyIterator;
		auto endIt = timelineKeys->begin();

		// if the time to find is above the next time
		if (newTime > (*currentIt)->getNextTime())
		{
			auto& tempIt = timelineKeyIterator;

			findTimeBackward(newTime-animationLength, animationLength);
			previousTime += animationLength;

			// start at the beginning of the timeline regardless of the startingPosition
			// and end at the startingPosition
			currentIt = std::prev(timelineKeys->end());
			endIt = tempIt;
		}

		real aTime = newTime;
		real bTime = previousTime;

		if (bTime < aTime)
		{
			if (aTime < (*currentIt)->getTime())
			{
				bTime += animationLength;
			}
			else
			{
				aTime -= animationLength;
			}
		}

		while (currentIt != endIt)
		{
			if ((*currentIt)->timeInRange(newTime))
			{
				timelineKeyIterator = currentIt;
				return;
			}

			checkTrigger(*currentIt, aTime, bTime);

			--currentIt;
		}

		checkTrigger(*currentIt, aTime, bTime);
		if ((*currentIt)->getTime() <= newTime)
		{
			timelineKeyIterator = currentIt;
			return;
		}
		else
		{
			timelineKeyIterator = std::prev(timelineKeys->end());
			return;
		}
	}

	void TriggerTimelineInstance::checkTrigger(TimelineKey *key, real aTime, real bTime)
	{
		if (aTime <= key->getTime() && key->getTime() < bTime)
		{
			triggerCount++;
		}
	}

}
