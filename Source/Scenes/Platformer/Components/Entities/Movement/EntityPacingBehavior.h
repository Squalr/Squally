#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;

class EntityPacingBehavior : public GameComponent
{
public:
	static EntityPacingBehavior* create(GameObject* owner);

	static const std::string MapKey;
	static const std::string PropertyTravelDistance;

protected:
	EntityPacingBehavior(GameObject* owner);
	virtual ~EntityPacingBehavior();

	void initializePositions() override;
	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	void assignDestination();
	void cancelPacing();

	PlatformerEntity* entity = nullptr;
	cocos2d::Vec2 spawnPosition;
	float maxTravelDistance = 0.0f;

	static const float DefaultTravelDistanceMin;
	static const float DefaultTravelDistanceMax;
	static const float MinimumPaceDistance;
};
