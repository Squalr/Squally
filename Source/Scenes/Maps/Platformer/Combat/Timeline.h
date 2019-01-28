#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class CProgressBar;
class PlatformerEntity;
class TimelineEntry;

class Timeline : public SmartNode
{
public:
	static Timeline* create();

	void initializeTimeline(std::vector<PlatformerEntity*> playerEntities, std::vector<PlatformerEntity*> enemyEntities, bool isPlayerFirstStrike);

private:
	typedef SmartNode super;
	Timeline();
	virtual ~Timeline() = default;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;
	void onCastStart(TimelineEntry* entry);

	CProgressBar* swordFill;
	cocos2d::Sprite* swordTop;
	cocos2d::Node* timelineNode;
	std::vector<PlatformerEntity*> playerEntities;
	std::vector<PlatformerEntity*> enemyEntities;
	std::vector<TimelineEntry*> timelineEntries;

	float timelineWidth;
	TimelineEntry* timelineEntryAwaitingUserAction;

	static const float TimelineSpeed;
};
