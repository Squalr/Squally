#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class EnemyAllyDropBehavior : public AttachedBehavior
{
public:
	static EnemyAllyDropBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EnemyAllyDropBehavior(GameObject* owner);
	virtual ~EnemyAllyDropBehavior();

	void initializePositions() override;
	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
