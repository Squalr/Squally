#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;

class EnemyAllyVisibilityBehavior : public Component
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
	typedef Component super;

	PlatformerEntity* entity;
};
