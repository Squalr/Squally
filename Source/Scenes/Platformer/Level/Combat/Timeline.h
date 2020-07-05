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
	
	std::vector<PlatformerEntity*> getEntities();
	std::vector<PlatformerEntity*> getFriendlyEntities();
	std::vector<PlatformerEntity*> getEnemyEntities();
	std::vector<PlatformerEntity*> getSameTeamEntities(PlatformerEntity* entity);
	std::vector<TimelineEntry*> getEntries();
	std::vector<TimelineEntry*> getFriendlyEntries();
	std::vector<TimelineEntry*> getEnemyEntries();
	std::vector<TimelineEntry*> getSameTeamEntries(PlatformerEntity* entity);
	TimelineEntry* getAssociatedEntry(PlatformerEntity* entity);
	std::vector<TimelineEntry*> initializeTimelineFriendly(const std::vector<PlatformerEntity*>& friendlyEntities);
	std::vector<TimelineEntry*> initializeTimelineEnemies(const std::vector<PlatformerEntity*>& enemyEntities);
	void initializeStartingProgress(bool isPlayerFirstStrike);

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
	void updateTimelineTargetMarkers();
	void refreshTimelinePositions();
	void registerTimelineEventGroup(TimelineEventGroup* timelineEventGroup);
	void unregisterTimelineEventGroup(TimelineEventGroup* timelineEventGroup);
	void onPauseStateChanged();

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
