#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;

class TimelineEntry : public SmartNode
{
public:
	static TimelineEntry* create(PlatformerEntity* entity, bool isPlayerEntry, std::function<void(TimelineEntry*)> onCastingStartCallback);

	bool isPlayerTimelineEntry();
	bool isCasting();
	void doCast();
	void interrupt();

	float cancelProgress();
	float getProgress();
	float addProgress(float progressDelta);
	float getSpeed();

	static const float CastPercentage;

private:
	typedef SmartNode super;
	TimelineEntry(PlatformerEntity* entity, bool isPlayerEntry, std::function<void(TimelineEntry*)> onCastingStartCallback);
	virtual ~TimelineEntry() = default;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	cocos2d::Sprite* line;
	cocos2d::Sprite* circle;
	cocos2d::Sprite* emblem;

	float speed;
	float progress;
	bool isPlayerEntry;
	std::function<void(TimelineEntry*)> onCastingStartCallback;
};
