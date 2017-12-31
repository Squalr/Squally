#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Entity.h"
#include "Collision/CategoryGroup.h"

using namespace cocos2d;

class Bat : public Entity
{
public:
	static Bat * create();

protected:
	bool contactBegin(CollisionData data) override;
	bool contactUpdate(CollisionData data) override;
	bool contactEnd(CollisionData data) override;

private:
	Bat();
	~Bat();

	void update(float) override;

	Animation* walkAnimation;
	Animation* jumpAnimation;
	Animation* deathAnimation;
};
