#pragma once

#include "Engine/Components/Component.h"

class CollisionObject;
class PlatformerEntity;

class EntityHeadCollisionBehavior : public Component
{
public:
	static EntityHeadCollisionBehavior* create(GameObject* owner);

	bool hasHeadCollisionWith(CollisionObject* collisonObject);
	
	CollisionObject* headCollision;

	static const std::string MapKey;

protected:
	EntityHeadCollisionBehavior(GameObject* owner);
	virtual ~EntityHeadCollisionBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	void buildHeadCollisionDetector();

	PlatformerEntity* entity;

	static const float HeadCollisionPadding;
	static const float HeadCollisionSize;
};
