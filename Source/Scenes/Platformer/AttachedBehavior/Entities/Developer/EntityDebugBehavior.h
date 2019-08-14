#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class PlatformerEntity;

class EntityDebugBehavior : public AttachedBehavior
{
public:
	static EntityDebugBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityDebugBehavior(GameObject* owner);
	~EntityDebugBehavior();

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
