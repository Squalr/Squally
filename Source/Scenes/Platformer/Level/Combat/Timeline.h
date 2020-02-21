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
class TimelineEventGroup;

class Timeline : public SmartNode
{
public:
	static Timeline* create();
	
	std::vector<TimelineEntry*> getEntries();
	std::vector<TimelineEntry*> initializeTimelineFriendly(bool isPlayerFirstStrike, std::vector<PlatformerEntity*> friendlyEntities);
	std::vector<TimelineEntry*> initializeTimelineEnemies(bool isPlayerFirstStrike, std::vector<PlatformerEntity*> enemyEntities);

	void resumeTimeline();

protected:
	Timeline();
	virtual ~Timeline();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

private:
	typedef SmartNode super;

	void checkCombatComplete();
	void updateTimeline(float dt);
	void registerTimelineEventGroup(TimelineEventGroup* timelineEventGroup);
	void unregisterTimelineEventGroup(TimelineEventGroup* timelineEventGroup);

	ProgressBar* swordFill;
	cocos2d::Sprite* swordTop;
	cocos2d::Node* eventsNode;
	cocos2d::Node* entriesNode;
	LocalizedLabel* waitLabel;
	LocalizedLabel* castLabel;
	std::vector<TimelineEntry*> timelineEntries;
	std::vector<TimelineEventGroup*> timelineEventGroups;

	float timelineWidth;
	bool isTimelinePaused;
	bool isTimelineCinematicPaused;
	bool isTimelineInterrupted;
	bool isCombatComplete;
	bool hasInit;
	TimelineEntry* timelineEntryAwaitingUserAction;
};
