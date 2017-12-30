#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Entity.h"
#include "Collision/CategoryGroup.h"

using namespace cocos2d;

class Snail : public Entity
{
public:
	static Snail * create();

	static int health;
	static Vec2 position;

protected:
	bool contactBegin(CollisionData data) override;
	bool contactUpdate(CollisionData data) override;
	bool contactEnd(CollisionData data) override;

private:
	Snail();
	~Snail();

	void update(float) override;

	Animation* walkAnimation;
	Animation* jumpAnimation;
	Animation* deathAnimation;
	bool canJump;
};
