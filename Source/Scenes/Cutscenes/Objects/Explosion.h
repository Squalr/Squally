#pragma once
#include "cocos2d.h"

#include "Engine/Utils/GameUtils.h"
#include "Resources.h"

using namespace cocos2d;

class Explosion : public Node
{
public:
	static Explosion* create(Vec2 speed);

private:
	Explosion(Vec2 speed);
	~Explosion();

	void onEnter() override;
	void update(float dt) override;

	Sprite* carSprite;
	Vec2 flySpeed;
};
