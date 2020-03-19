#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class EnemyBattleAllyBehavior : public AttachedBehavior
{
public:
	static EnemyBattleAllyBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EnemyBattleAllyBehavior(GameObject* owner);
	virtual ~EnemyBattleAllyBehavior();

	void initializePositions() override;
	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
