#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class PlatformerEntity;

class EntitySelectionBehavior : public AttachedBehavior
{
public:
	static EntitySelectionBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);
	
	void setEntityClickCallbacks(std::function<void()> onClick, std::function<void()> onMouseOver);
	void clearEntityClickCallbacks();

	static const std::string MapKeyAttachedBehavior;

protected:
	EntitySelectionBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~EntitySelectionBehavior();

	void initializePositions() override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	
	ClickableNode* clickHitbox;
};
