#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class EntityPacingBehavior : public AttachedBehavior
{
public:
	static EntityPacingBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EntityPacingBehavior(GameObject* owner);
	virtual ~EntityPacingBehavior();

	void initializePositions() override;
	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	void assignDestination();
	void cancelPacing();

	PlatformerEntity* entity;
	cocos2d::Vec2 anchorPosition;
	float destinationDelta;

	static const float TravelDistanceMin;
	static const float TravelDistanceMax;
};
