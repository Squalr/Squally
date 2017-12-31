#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Entity.h"
#include "Collision/CategoryGroup.h"

using namespace cocos2d;

class Shroom : public Entity
{
public:
	static Shroom * create();

protected:
	bool contactBegin(CollisionData data) override;
	bool contactUpdate(CollisionData data) override;
	bool contactEnd(CollisionData data) override;

private:
	Shroom();
	~Shroom();

	void update(float) override;

	Animation* walkAnimation;
	Animation* jumpAnimation;
	Animation* deathAnimation;
};
