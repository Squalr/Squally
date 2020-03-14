#pragma once

#include "Engine/SmartNode.h"

class Buff;
class PlatformerEntity;
class TimelineEvent;

class TimelineEventGroup : public SmartNode
{
public:
	static TimelineEventGroup* create(std::vector<TimelineEvent*> timelineEvents, Buff* associatedBuff, PlatformerEntity* owner, std::function<void()> onGroupComplete = nullptr);

	void setPositions(float timelineWidth);
	void offsetByTimelineTime(float initialTime);
	Buff* getAssociatedBuff();
	PlatformerEntity* getOwner();
	bool processEvents(float previousTime, float currentTime);

protected:
	TimelineEventGroup(std::vector<TimelineEvent*> timelineEvents, Buff* associatedBuff, PlatformerEntity* owner, std::function<void()> onGroupComplete);
	virtual ~TimelineEventGroup();

	void initializeListeners() override;

private:
	typedef SmartNode super;

	void removeAllTimelineEvents();
	void registerTimelineEvent(TimelineEvent* timelineEvent);
	void unregisterTimelineEvent(TimelineEvent* timelineEvent);

	cocos2d::Node* timelineEventsNode;

	Buff* associatedBuff;
	PlatformerEntity* owner;
	std::vector<TimelineEvent*> timelineEvents;
	std::vector<TimelineEvent*> timelineEventsToDelete;
	std::function<void()> onGroupComplete;
};
