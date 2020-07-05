#include "TimelineEventGroup.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"

using namespace cocos2d;

TimelineEventGroup* TimelineEventGroup::create(std::vector<TimelineEvent*> timelineEvents, Buff* associatedBuff, PlatformerEntity* owner, std::function<void()> onGroupComplete)
{
	TimelineEventGroup* instance = new TimelineEventGroup(timelineEvents, associatedBuff, owner, onGroupComplete);

	instance->autorelease();

	return instance;
}

TimelineEventGroup::TimelineEventGroup(std::vector<TimelineEvent*> timelineEvents, Buff* associatedBuff, PlatformerEntity* owner, std::function<void()> onGroupComplete)
{
	this->timelineEventsNode = Node::create();
	this->timelineEvents = timelineEvents;
	this->timelineEventsToDelete = std::vector<TimelineEvent*>();
	this->onGroupComplete = onGroupComplete;
	this->associatedBuff = associatedBuff;
	this->owner = owner;

	for (auto event : this->timelineEvents)
	{
		this->timelineEventsNode->addChild(event);
	}

	this->addChild(this->timelineEventsNode);
}

TimelineEventGroup::~TimelineEventGroup()
{
}

void TimelineEventGroup::initializeListeners()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventBuffRemoved, [=](EventCustom* eventCustom)
	{
		CombatEvents::BuffRemovedArgs* args = static_cast<CombatEvents::BuffRemovedArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->buff == this->getAssociatedBuff())
		{
			this->removeAllTimelineEvents();
		}
	}));
}

Buff* TimelineEventGroup::getAssociatedBuff()
{
	return this->associatedBuff;
}

PlatformerEntity* TimelineEventGroup::getOwner()
{
	return this->owner;
}

void TimelineEventGroup::setPositions(float timelineWidth)
{
	for (auto timelineEvent : this->timelineEvents)
	{
		timelineEvent->setPositions(timelineWidth);
	}
}

void TimelineEventGroup::offsetByTimelineTime(float initialTime)
{
	for (auto timelineEvent : this->timelineEvents)
	{
		timelineEvent->offsetByTimelineTime(initialTime);
	}
}

bool TimelineEventGroup::processEvents(float previousTime, float currentTime)
{
	for (auto timelineEvent : this->timelineEvents)
	{
		if (timelineEvent->tryUpdateEvent(previousTime, currentTime))
		{
			this->timelineEventsToDelete.push_back(timelineEvent);
		}
	}
	
	for (auto timelineEvent : this->timelineEventsToDelete)
	{
		this->unregisterTimelineEvent(timelineEvent);
	}

	this->timelineEventsToDelete.clear();

	if (this->timelineEvents.empty() && this->onGroupComplete != nullptr)
	{
		this->onGroupComplete();
	}

	return this->timelineEvents.empty();
}

void TimelineEventGroup::removeAllTimelineEvents()
{
	for (auto next : this->timelineEvents)
	{
		next->deactivate();
	}
	
	this->timelineEvents.clear();

	if (this->timelineEvents.empty() && this->onGroupComplete != nullptr)
	{
		this->onGroupComplete();
	}
}

void TimelineEventGroup::unregisterTimelineEvent(TimelineEvent* timelineEvent)
{
	if (timelineEvent == nullptr)
	{
		return;
	}

	timelineEvent->deactivate();

	this->timelineEvents.erase(std::remove(this->timelineEvents.begin(), this->timelineEvents.end(), timelineEvent), this->timelineEvents.end());
}
