#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class DrawNode;
}

class PlatformerEntity;

class EntityProjectileTargetBehavior : public AttachedBehavior
{
public:
	static EntityProjectileTargetBehavior* create(GameObject* owner);

	cocos2d::Node* getTarget();

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityProjectileTargetBehavior(GameObject* owner);
	~EntityProjectileTargetBehavior();

	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;
	void onLoad() override;
	void initializePositions() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;

	cocos2d::DrawNode* projectileTarget;
};
