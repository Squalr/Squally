#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Components/InfiniteParallaxNode.h"
#include "GUI/Components/MenuSprite.h"
#include "GUI/Components/Mouse.h"

using namespace cocos2d;

class MenuBackground : public Node
{
public:
	static MenuBackground * claimInstance();
	static MenuBackground * getInstance();

protected:
	MenuBackground();
	~MenuBackground();

private:
	void onEnter() override;
	void InitializePositions();

	Sprite* background;
	Sprite* backgroundVines;
	Sprite* backgroundTrees;
	Sprite* midgroundTrees;
	Sprite* foregroundVines;
	InfiniteParallaxNode* fog;
	InfiniteParallaxNode* foregroundFog;
	Sprite* foregroundGrassBottom;
	Sprite* foregroundGrassTop;
	Sprite* foregroundLight;
	ParticleSystem* matrixParticles;
	ParticleSystem* windParticles;
	ParticleSystem* fireflyParticles;
};

