#pragma once

#include "Scenes/Platformer/AttachedBehaviors/Entities/Stats/EntityEqBehaviorBase.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class PlatformerEntity;

class SquallyEqBehavior : public EntityEqBehaviorBase
{
public:
	static SquallyEqBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyEqBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyEqBehavior();

	void onLoad() override;

private:
	typedef EntityEqBehaviorBase super;
	
	void saveState();
};
