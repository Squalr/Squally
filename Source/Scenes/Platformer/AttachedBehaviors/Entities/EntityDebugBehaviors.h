#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class PlatformerEntity;

class EntityDebugBehaviors : public AttachedBehavior
{
public:
	static EntityDebugBehaviors* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityDebugBehaviors(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityDebugBehaviors();

	void initializePositions() override;
	void onDeveloperModeEnable() override;
	void onDeveloperModeDisable() override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	
	ClickableNode* resurrectButton;
	ClickableNode* killButton;
};
