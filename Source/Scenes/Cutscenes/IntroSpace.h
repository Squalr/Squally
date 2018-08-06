#pragma once
#include "cocos2d.h"

#include "Engine/Input/InputManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"
#include "Scenes/Cutscenes/Cutscene.h"

using namespace cocos2d;

class IntroSpace : public Cutscene
{
public:
	static IntroSpace* create();

protected:
	IntroSpace();
	~IntroSpace();

private:
	void onEnter() override;
	void update(float) override;
	void initializePositions();
	void initializeListeners();
	void endCutscene();

	Layer* starsLayer;
	Sprite* earth;
	Sprite* mars;
	Sprite* weaver1;
	Animation* weaver1Anim;
	Sprite* weaver2;
	Animation* weaver2Anim;
	Sprite* weaver3;
	Animation* weaver3Anim;
	Sprite* weaver4;
	Animation* weaver4Anim;
	Sprite* weaver5;
	Animation* weaver5Anim;
};
