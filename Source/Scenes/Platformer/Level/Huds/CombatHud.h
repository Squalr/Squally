#pragma once

#include "Engine/UI/HUD/Hud.h"

class TimelineEntry;
class StatsBars;

class CombatHud : public Hud
{
public:
	static CombatHud* create();

	void bindStatsBars(std::vector<TimelineEntry*> friendlyEntries, std::vector<TimelineEntry*> enemyEntries);

protected:
	CombatHud();
	virtual ~CombatHud();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef Hud super;
	
	cocos2d::Node* playerPartyStatsNode;
	cocos2d::Node* enemyPartyStatsNode;

	std::vector<StatsBars*> playerPartyStatsBars;
	std::vector<StatsBars*> enemyPartyStatsBars;
};
