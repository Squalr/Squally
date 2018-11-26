#pragma once
#include "cocos2d.h"

#include "Engine/Utils/GameUtils.h"
#include "Resources/CutsceneResources.h"

using namespace cocos2d;

class Explosion : public Node
{
public:
	static Explosion* create();

private:
	Explosion();
	~Explosion();

	void onEnter() override;

	LayerColor* explosion;
};
