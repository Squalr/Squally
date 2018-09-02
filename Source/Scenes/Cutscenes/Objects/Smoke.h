#pragma once
#include "cocos2d.h"

#include "Engine/Utils/GameUtils.h"
#include "Resources.h"

using namespace cocos2d;

class Smoke : public Node
{
public:
	static Smoke* create(Node* followTarget);

	void stopFollow();

private:
	Smoke(Node* followTarget);
	~Smoke();

	void onEnter() override;

	Node* follow;
	Sprite* smokeSprite;
	Animation* smokeAnimation;

	static const std::string ScheduleKeySpawnSmoke;
};
