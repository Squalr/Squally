#pragma once
#include "cocos2d.h"

#include "Engine/SmartNode.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/FloatingSprite.h"
#include "Engine/UI/InfiniteParallaxNode.h"
#include "Engine/UI/Mouse.h"
#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

class MenuBackground : public SmartNode
{
public:
	static MenuBackground * claimInstance();
	static MenuBackground * getInstance();

private:
	MenuBackground();
	~MenuBackground();

	void initializePositions() override;

	Sprite* background;
	FloatingSprite* backgroundTrees;
	FloatingSprite* midgroundTrees;
	FloatingSprite* foregroundVines;
	InfiniteParallaxNode* fog;
	InfiniteParallaxNode* foregroundFog;
	FloatingSprite* foregroundGrassBottom;
	FloatingSprite* foregroundGrassTop;
	Sprite* webs;
	Sprite* foregroundLight;

	ParticleSystem* windParticles;
	ParticleSystem* fireflyParticles;

	static MenuBackground* menuBackgroundInstance;
};

