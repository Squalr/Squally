#pragma once

#include "Engine/SmartNode.h"

class PlatformerAttack;
class PlatformerEntity;
class TimelineEntry;

class EnemyAIHelper : public SmartNode
{
public:
	static EnemyAIHelper* create();

private:
	typedef SmartNode super;
	EnemyAIHelper();
	virtual ~EnemyAIHelper() = default;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	void performAIActions(TimelineEntry* attackingEntity);
	PlatformerAttack* selectAttack(TimelineEntry* attackingEntity, std::vector<PlatformerEntity*> playerEntities, std::vector<PlatformerEntity*> enemyEntities);
	PlatformerEntity* selectTarget(TimelineEntry* attackingEntity, std::vector<PlatformerEntity*> playerEntities, std::vector<PlatformerEntity*> enemyEntities);
};
