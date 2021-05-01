#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;

class EnemyAllyDropBehavior : public Component
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
	typedef Component super;

	PlatformerEntity* entity;
};
