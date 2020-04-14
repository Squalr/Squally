#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class EnemyAllyVisibilityBehavior : public AttachedBehavior
{
public:
	static EnemyAllyVisibilityBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EnemyAllyVisibilityBehavior(GameObject* owner);
	virtual ~EnemyAllyVisibilityBehavior();

	void initializePositions() override;
	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
