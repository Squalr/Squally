#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class EntityPacingBehavior : public AttachedBehavior
{
public:
	static EntityPacingBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityPacingBehavior(GameObject* owner);
	~EntityPacingBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void assignDestination();

	PlatformerEntity* entity;
	cocos2d::Vec2 anchorPosition;

	static const float TravelDistanceMax;
};
