#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;

class EntityPacingBehavior : public Component
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
	typedef Component super;

	void assignDestination();
	void cancelPacing();

	PlatformerEntity* entity;
	cocos2d::Vec2 spawnPosition;
	float maxTravelDistance;

	static const float DefaultTravelDistanceMin;
	static const float DefaultTravelDistanceMax;
	static const float MinimumPaceDistance;
};
