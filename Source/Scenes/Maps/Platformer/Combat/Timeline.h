#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class PlatformerEntity;
class ProgressBar;
class TimelineEntry;

class Timeline : public SmartNode
{
public:
	static Timeline* create();

	void initializeTimeline(std::vector<PlatformerEntity*> playerEntities, std::vector<PlatformerEntity*> enemyEntities, bool isPlayerFirstStrike);
	void resumeTimeline();

private:
	typedef SmartNode super;
	Timeline();
	virtual ~Timeline() = default;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	void checkCombatComplete();
	void updateTimeline(float dt);

	ProgressBar* swordFill;
	cocos2d::Sprite* swordTop;
	cocos2d::Node* timelineNode;
	LocalizedLabel* waitLabel;
	LocalizedLabel* castLabel;
	std::vector<PlatformerEntity*> playerEntities;
	std::vector<PlatformerEntity*> enemyEntities;
	std::vector<TimelineEntry*> timelineEntries;

	float timelineWidth;
	bool isTimelinePaused;
	bool isCombatComplete;
	TimelineEntry* timelineEntryAwaitingUserAction;

	static const float TimelineSpeed;
};
