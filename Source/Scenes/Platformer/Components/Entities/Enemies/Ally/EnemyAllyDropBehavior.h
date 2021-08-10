#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;

class EnemyAllyDropBehavior : public GameComponent
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
	typedef GameComponent super;

	PlatformerEntity* entity;
};
