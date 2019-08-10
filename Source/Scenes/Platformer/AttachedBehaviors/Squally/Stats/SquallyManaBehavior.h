#pragma once

#include "Scenes/Platformer/AttachedBehaviors/Entities/Stats/EntityManaBehaviorBase.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class PlatformerEntity;

class SquallyManaBehavior : public EntityManaBehaviorBase
{
public:
	static SquallyManaBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyManaBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyManaBehavior();

	void onLoad() override;

private:
	typedef EntityManaBehaviorBase super;
	
	void saveState();
};
