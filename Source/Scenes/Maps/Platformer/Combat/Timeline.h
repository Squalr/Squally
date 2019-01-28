#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class CProgressBar;
class LocalizedLabel;
class PlatformerEntity;
class TimelineEntry;

class Timeline : public SmartNode
{
public:
	static Timeline* create(std::function<void(PlatformerEntity*)> onUserActionRequiredCallback);

	void initializeTimeline(std::vector<PlatformerEntity*> playerEntities, std::vector<PlatformerEntity*> enemyEntities, bool isPlayerFirstStrike);
	void actionMade();

private:
	typedef SmartNode super;
	Timeline(std::function<void(PlatformerEntity*)> onUserActionRequiredCallback);
	virtual ~Timeline() = default;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;
	void onCastStart(TimelineEntry* entry);

	CProgressBar* swordFill;
	cocos2d::Sprite* swordTop;
	cocos2d::Node* timelineNode;
	LocalizedLabel* waitLabel;
	LocalizedLabel* castLabel;
	std::vector<PlatformerEntity*> playerEntities;
	std::vector<PlatformerEntity*> enemyEntities;
	std::vector<TimelineEntry*> timelineEntries;

	float timelineWidth;
	TimelineEntry* timelineEntryAwaitingUserAction;
	std::function<void(PlatformerEntity*)> onUserActionRequiredCallback;

	static const float TimelineSpeed;
};
