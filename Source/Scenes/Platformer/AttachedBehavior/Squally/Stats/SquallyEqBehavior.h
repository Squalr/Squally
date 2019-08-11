#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityEqBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class PlatformerEntity;

class SquallyEqBehavior : public EntityEqBehavior
{
public:
	static SquallyEqBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyEqBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyEqBehavior();

	void onLoad() override;

private:
	typedef EntityEqBehavior super;
	
	void saveState();
};
