#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Entity.h"
#include "Objects/Collision/CategoryGroup.h"

using namespace cocos2d;

class Knight : public Entity
{
public:
	static Knight * create();

protected:
	bool contactBegin(CollisionData data) override;
	bool contactUpdate(CollisionData data) override;
	bool contactEnd(CollisionData data) override;

private:
	Knight();
	~Knight();

	void update(float) override;

	Animation* walkAnimation;
	Animation* jumpAnimation;
	Animation* deathAnimation;

	Sprite* knightSprite;
};
