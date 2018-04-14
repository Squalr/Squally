#include "timelineinstance.h"

#include "../global/settings.h"

#include "../entity/entityinstance.h"

#include "timeline.h"
#include "timelinekey.h"

namespace SpriterEngine
{

	TimelineInstance::TimelineInstance(Timeline *timeline) :
		resultObject(0)
	{
		timeline->setupTimelineInstance(&timelineKeys);
		timelineKeyIterator = timelineKeys->begin();
	}

	TimelineInstance::~TimelineInstance()
	{
	}

	void TimelineInstance::findCurrentTimelineKey(real newTime, bool forward, real animationLength)
	{
		if (forward)
		{
			findTimeForward(newTime);
		}
		else
		{
			findTimeBackward(newTime);
		}
	}

	void TimelineInstance::processCurrentTimelineKey(real newTime)
	{
		(*timelineKeyIterator)->process(newTime, resultObject);
	}

	void TimelineInstance::blendCurrentTimelineKey(real newTime, real blendRatio)
	{
		(*timelineKeyIterator)->blend(newTime, blendRatio, resultObject);
	}

	void TimelineInstance::findTimeForward(real newTime)
	{
		auto& currentIt = timelineKeyIterator;
		auto endIt = std::prev(timelineKeys->end());

		// if the time to find is below the current time
		if (newTime<(*currentIt)->getTime())
		{
			// start at the beginning of the timeline regardless of the startingPosition
			// and end at the startingPosition
			currentIt = timelineKeys->begin();
			endIt = timelineKeyIterator;
		}

		while (currentIt != endIt)
		{
			if ((*currentIt)->timeInRange(newTime))
			{
				timelineKeyIterator = currentIt;
				return;
			}
			++currentIt;
		}

		if ((*currentIt)->getTime() <= newTime)
		{
			timelineKeyIterator = currentIt;
			return;
		}
		else
		{
			Settings::error("TimelineInstance::findTimeForward - could not find key at time " + std::to_string(newTime) + " : falling back on first key");
			timelineKeyIterator = timelineKeys->begin();
			return;
		}
	}

	void TimelineInstance::findTimeBackward(real newTime)
	{
		auto& currentIt = timelineKeyIterator;
		auto endIt = timelineKeys->begin();

		// if the time to find is above the next time
		if (newTime > (*currentIt)->getNextTime())
		{
			// if the time to find is after the last keyframe
			if (newTime >= timelineKeys->back()->getTime())
			{
				// then the last keyframe in the timeline is the correct result
				timelineKeyIterator = --timelineKeys->end();
				return;
			}
			else
			{
				// if not, start at the end of the timeline regardless of the startingPosition
				// and end at the startingPosition
				currentIt = --timelineKeys->end();
			}
		}

		while (currentIt != endIt)
		{
			if ((*currentIt)->timeInRange(newTime))
			{
				timelineKeyIterator = currentIt;
				return;
			}
			--currentIt;
		}

		if ((*currentIt)->getTime() <= newTime)
		{
			timelineKeyIterator = currentIt;
			return;
		}
		else
		{
			Settings::error("TimelineInstance::findTimeBackward - could not find key at time " + std::to_string(newTime) + " : falling back on first key");
			timelineKeyIterator = timelineKeys->begin();
			return;
		}
	}

}
