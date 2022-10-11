#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;

class EnemyAllyVisibilityBehavior : public GameComponent
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
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;
};
