#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class PlatformerEntity;

class EntityHealthBehavior : public AttachedBehavior
{
public:
	static EntityHealthBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);

protected:
	EntityHealthBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityHealthBehavior();

	void onLoad() override;

	PlatformerEntity* entity;

private:
	typedef AttachedBehavior super;

	int getHealth();
	void addHealth(int healthDelta);
	void setHealth(int health);
	int getMaxHealth();
	bool isAlive();
	bool isDead();
	virtual void kill(bool loadDeadAnim = true);
	virtual void killAndRespawn();
	virtual void revive();

	cocos2d::Vec2 spawnCoords;
};
