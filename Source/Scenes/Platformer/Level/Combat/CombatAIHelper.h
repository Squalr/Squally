#pragma once

#include "Engine/SmartNode.h"

class PlatformerAttack;
class PlatformerEntity;
class TimelineEntry;

class CombatAIHelper : public SmartNode
{
public:
	static CombatAIHelper* create();

	void initializeEntities(std::vector<PlatformerEntity*> playerEntities, std::vector<PlatformerEntity*> enemyEntities);

private:
	typedef SmartNode super;
	CombatAIHelper();
	virtual ~CombatAIHelper() = default;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	void performRetargetCorrections(TimelineEntry* attackingEntry);
	void performAIActions(TimelineEntry* attackingEntry);
	void selectTarget(TimelineEntry* attackingEntry);
	void selectAttack(TimelineEntry* attackingEntry);

	std::vector<PlatformerEntity*> playerEntities;
	std::vector<PlatformerEntity*> enemyEntities;
	PlatformerEntity* selectedTarget;
	PlatformerAttack* selectedAttack;
};
