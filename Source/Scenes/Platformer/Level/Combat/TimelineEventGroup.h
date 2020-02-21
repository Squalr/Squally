#pragma once

#include "Engine/SmartNode.h"

class PlatformerEntity;
class TimelineEvent;

class TimelineEventGroup : public SmartNode
{
public:
	static TimelineEventGroup* create(std::vector<TimelineEvent*> timelineEvents, PlatformerEntity* owner, std::function<void()> onGroupComplete = nullptr);

	void setPositions(float timelineWidth);
	void offsetByTimelineTime(float initialTime);
	PlatformerEntity* getOwner();
	bool processEvents(float previousTime, float currentTime);

protected:
	TimelineEventGroup(std::vector<TimelineEvent*> timelineEvents, PlatformerEntity* owner, std::function<void()> onGroupComplete);
	virtual ~TimelineEventGroup();

private:
	typedef SmartNode super;

	void registerTimelineEvent(TimelineEvent* timelineEvent);
	void unregisterTimelineEvent(TimelineEvent* timelineEvent);

	PlatformerEntity* owner;
	std::vector<TimelineEvent*> timelineEvents;
	std::function<void()> onGroupComplete;
};
