#pragma once
#include "cocos2d.h"

#include "Engine/Rendering/Components/FloatingSprite.h"
#include "Engine/Rendering/Components/InfiniteParallaxNode.h"
#include "Engine/Rendering/Components/MenuSprite.h"
#include "Engine/Rendering/Components/Mouse.h"
#include "Resources.h"

using namespace cocos2d;

class MenuBackground : public Node
{
public:
	static MenuBackground * claimInstance();
	static MenuBackground * getInstance();

	void initializePositions();

private:
	MenuBackground();
	~MenuBackground();

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

