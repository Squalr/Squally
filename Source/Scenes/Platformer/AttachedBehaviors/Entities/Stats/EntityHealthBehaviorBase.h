#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class PlatformerEntity;

class EntityHealthBehaviorBase : public AttachedBehavior
{
public:
	int getHealth();
	void addHealth(int healthDelta);
	void setHealth(int health);
	int getMaxHealth();
	bool isAlive();
	bool isDead();
	virtual void kill(bool loadDeadAnim = true);
	virtual void killAndRespawn();
	virtual void revive();

protected:
	EntityHealthBehaviorBase(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityHealthBehaviorBase();

	void onLoad() override;

	PlatformerEntity* entity;

private:
	typedef AttachedBehavior super;
};
