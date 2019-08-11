#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityHealthBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class PlatformerEntity;

class SquallyHealthBehavior : public EntityHealthBehavior
{
public:
	static SquallyHealthBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyHealthBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyHealthBehavior();

	void onLoad() override;

private:
	typedef EntityHealthBehavior super;
	
	void saveState();
};
