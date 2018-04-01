#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Entity.h"
#include "Objects/Collision/CategoryGroup.h"

using namespace cocos2d;

class RedDragon1 : public Entity
{
public:
	static RedDragon1 * create();

protected:
	bool contactBegin(CollisionData data) override;
	bool contactUpdate(CollisionData data) override;
	bool contactEnd(CollisionData data) override;

private:
	RedDragon1();
	~RedDragon1();

	void update(float) override;

	Animation* walkAnimation;
	Animation* deathAnimation;

	Sprite* sprite;
};
