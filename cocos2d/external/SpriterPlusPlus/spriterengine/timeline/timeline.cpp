#include "timeline.h"

#include "../global/settings.h"

#include "timelineinstance.h"

namespace SpriterEngine
{

	Timeline::Timeline(int initialObjectId):
		objectId(initialObjectId)
	{
	}

	Timeline::~Timeline()
	{
		for (auto& it : keys)
		{
			delete it;
		}
	}

	int Timeline::getObjectId()
	{
		return objectId;
	}

	TimelineKey *Timeline::pushBackKey(TimeInfo *initialTimeInfo, UniversalObjectInterface *initialObjectInfo)
	{
		keys.push_back(new TimelineKey(initialTimeInfo, initialObjectInfo));
		return keys.back();
	}

	TimelineKey *Timeline::pushFrontProxyKey(real initialTime, real initialNextTime, bool isLooping)
	{
		if (keys.size())
		{
			if (isLooping)
			{
				keys.insert(keys.begin(), keys.back()->newProxyKey(initialTime, initialNextTime, false));
			}
			else
			{
				keys.insert(keys.begin(), keys.front()->newProxyKey(initialTime, initialNextTime, true));
			}
			return keys.front();
		}
		else
		{
			Settings::error("Timeline::pushFrontProxyKey - timeline has no key : cannot create proxy key");
			return 0;
		}
	}

	TimelineKey *Timeline::getKey(int keyIndex)
	{
		if (keyIndex < keys.size())
		{
			return keys.at(keyIndex);
		}
		else
		{
			Settings::error("Timeline::getKey - key index " + std::to_string(keyIndex) + " out of range");
			return 0;
		}
	}

	TimelineKey *Timeline::getLastKey()
	{
		if (keys.size())
		{
			return keys.back();
		}
		else
		{
			return 0;
		}
	}

	void Timeline::setupTimelineInstance(TimelineKeyVector **keyInstances)
	{
		*keyInstances = &keys;
	}

}
