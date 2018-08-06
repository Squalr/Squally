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
	void createStars();
	void initializePositions();
	void initializeListeners();
	void endCutscene();

	enum Stars {
		StarSmall,
		StarMedium,
		StarLarge,
		StarShineSmall,
		StarShineSmallHallow,
		StarShineLarge,
		StarShineExtraLarge,
	};

	static std::map<Stars, int> frequencyMap;

	Node* starsLayer;
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
