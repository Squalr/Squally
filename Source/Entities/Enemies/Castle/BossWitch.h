#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Entity.h"
#include "Objects/Collision/CategoryGroup.h"

using namespace cocos2d;

class BossWitch : public Entity
{
public:
	static BossWitch * create();

protected:
	bool contactBegin(CollisionData data) override;
	bool contactUpdate(CollisionData data) override;
	bool contactEnd(CollisionData data) override;

private:
	BossWitch();
	~BossWitch();

	void update(float) override;

	Animation* walkAnimation;
	Animation* deathAnimation;

	Sprite* sprite;
};
