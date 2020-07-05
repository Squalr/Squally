#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;

class TimelineEvent : public SmartNode
{
public:
	static TimelineEvent* create(PlatformerEntity* owner, cocos2d::Sprite* emblem, float offsetTime, std::function<void()> timelineEvent);

	PlatformerEntity* getOwner();
	void deactivate();
	void setPositions(float timelineWidth);
	void offsetByTimelineTime(float initialTime);
	float getTime();
	void setTime(float time);
	bool tryUpdateEvent(float previousTime, float currentTime);
	bool isPlayerEntry();

protected:
	TimelineEvent(PlatformerEntity* owner, cocos2d::Sprite* emblem, float offsetTime, std::function<void()> timelineEvent);
	virtual ~TimelineEvent();

	void initializePositions() override;

private:
	typedef SmartNode super;

	PlatformerEntity* owner;
	cocos2d::Sprite* line;
	cocos2d::Sprite* circle;
	cocos2d::Sprite* emblem;
	float time;
	std::function<void()> timelineEvent;
	bool isDeactivated;
};
