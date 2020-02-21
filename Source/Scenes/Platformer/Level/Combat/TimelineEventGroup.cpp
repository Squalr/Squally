#include "TimelineEventGroup.h"

#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"

using namespace cocos2d;

TimelineEventGroup* TimelineEventGroup::create(std::vector<TimelineEvent*> timelineEvents, PlatformerEntity* owner, std::function<void()> onGroupComplete)
{
	TimelineEventGroup* instance = new TimelineEventGroup(timelineEvents, owner, onGroupComplete);

	instance->autorelease();

	return instance;
}

TimelineEventGroup::TimelineEventGroup(std::vector<TimelineEvent*> timelineEvents, PlatformerEntity* owner, std::function<void()> onGroupComplete)
{
	this->timelineEvents = timelineEvents;
	this->onGroupComplete = onGroupComplete;
	this->owner = owner;

	for (auto event : this->timelineEvents)
	{
		this->addChild(event);
	}
}

TimelineEventGroup::~TimelineEventGroup()
{
}

PlatformerEntity* TimelineEventGroup::getOwner()
{
	return this->owner;
}

void TimelineEventGroup::setPositions(float timelineWidth)
{
	for (auto event : this->timelineEvents)
	{
		event->setPositions(timelineWidth);
	}
}

void TimelineEventGroup::offsetByTimelineTime(float initialTime)
{
	for (auto event : this->timelineEvents)
	{
		event->offsetByTimelineTime(initialTime);
	}
}

bool TimelineEventGroup::processEvents(float previousTime, float currentTime)
{
	for (auto event : this->timelineEvents)
	{
		if (event->tryUpdateEvent(previousTime, currentTime))
		{
			this->unregisterTimelineEvent(event);
		}
	}

	if (this->timelineEvents.empty() && this->onGroupComplete != nullptr)
	{
		this->onGroupComplete();
	}

	return this->timelineEvents.empty();
}

void TimelineEventGroup::unregisterTimelineEvent(TimelineEvent* timelineEvent)
{
	this->timelineEvents.erase(std::remove(this->timelineEvents.begin(), this->timelineEvents.end(), timelineEvent), this->timelineEvents.end());
	this->removeChild(timelineEvent);
}
