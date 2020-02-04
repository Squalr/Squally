#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class EnemyBattleAllyBehavior : public AttachedBehavior
{
public:
	static EnemyBattleAllyBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	EnemyBattleAllyBehavior(GameObject* owner);
	virtual ~EnemyBattleAllyBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
