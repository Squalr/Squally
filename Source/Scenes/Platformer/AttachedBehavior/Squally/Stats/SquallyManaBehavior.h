#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityManaBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class PlatformerEntity;

class SquallyManaBehavior : public EntityManaBehavior
{
public:
	static SquallyManaBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyManaBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyManaBehavior();

	void onLoad() override;

private:
	typedef EntityManaBehavior super;
	
	void saveState();
};
