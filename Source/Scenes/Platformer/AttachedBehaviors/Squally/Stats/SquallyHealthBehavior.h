#pragma once

#include "Scenes/Platformer/AttachedBehaviors/Entities/Stats/EntityHealthBehaviorBase.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class PlatformerEntity;

class SquallyHealthBehavior : public EntityHealthBehaviorBase
{
public:
	static SquallyHealthBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyHealthBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyHealthBehavior();

	void onLoad() override;

private:
	typedef EntityHealthBehaviorBase super;
	
	void saveState();
};
