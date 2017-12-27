#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Components/InfiniteParallaxNode.h"
#include "GUI/Components/MenuSprite.h"
#include "GUI/Components/FloatingSprite.h"
#include "GUI/Components/Mouse.h"

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

