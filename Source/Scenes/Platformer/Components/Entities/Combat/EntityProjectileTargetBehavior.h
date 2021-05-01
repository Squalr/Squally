#pragma once

#include "Engine/Components/Component.h"

namespace cocos2d
{
	class DrawNode;
}

class PlatformerEntity;

class EntityProjectileTargetBehavior : public Component
{
public:
	static EntityProjectileTargetBehavior* create(GameObject* owner);

	cocos2d::Node* getTarget();

	static const std::string MapKey;

protected:
	EntityProjectileTargetBehavior(GameObject* owner);
	virtual ~EntityProjectileTargetBehavior();

	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;
	void onLoad() override;
	void onDisable() override;
	void initializePositions() override;

private:
	typedef Component super;

	PlatformerEntity* entity;

	cocos2d::Node* projectileTarget;
};
