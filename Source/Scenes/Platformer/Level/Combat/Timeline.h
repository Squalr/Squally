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
	
	std::vector<TimelineEntry*> getEntries();
	std::vector<TimelineEntry*> initializeTimelineFriendly(bool isPlayerFirstStrike, std::vector<PlatformerEntity*> friendlyEntities);
	std::vector<TimelineEntry*> initializeTimelineEnemies(bool isPlayerFirstStrike, std::vector<PlatformerEntity*> enemyEntities);

	void resumeTimeline();

private:
	typedef SmartNode super;
	Timeline();
	virtual ~Timeline();

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
	std::vector<TimelineEntry*> timelineEntries;

	float timelineWidth;
	bool isTimelinePaused;
	bool isTimelineInterrupted;
	bool isCombatComplete;
	bool hasInit;
	TimelineEntry* timelineEntryAwaitingUserAction;
};
