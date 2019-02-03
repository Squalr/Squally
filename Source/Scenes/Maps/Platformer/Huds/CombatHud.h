#pragma once

#include "Engine/UI/HUD/Hud.h"

class PlatformerEntity;
class StatsBars;

class CombatHud : public Hud
{
public:
	static CombatHud* create();

	void bindStatsBars(std::vector<PlatformerEntity*> playerParty, std::vector<PlatformerEntity*> enemyParty);

private:
	typedef Hud super;
	CombatHud();
	virtual ~CombatHud();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	cocos2d::Node* playerPartyStatsNode;
	cocos2d::Node* enemyPartyStatsNode;

	std::vector<StatsBars*> playerPartyStatsBars;
	std::vector<StatsBars*> enemyPartyStatsBars;
};
