#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class ParticleSystem;
	class Sprite;
}

class InfiniteParallaxNode;
class FloatingSprite;

class MenuBackground : public SmartNode
{
public:
	static MenuBackground* claimInstance();
	static MenuBackground* getInstance();

private:
	typedef SmartNode super;
	MenuBackground();
	~MenuBackground();

	void initializePositions() override;

	cocos2d::Sprite* background;
	FloatingSprite* backgroundTrees;
	FloatingSprite* midgroundTrees;
	FloatingSprite* foregroundVines;
	InfiniteParallaxNode* fog;
	InfiniteParallaxNode* foregroundFog;
	FloatingSprite* foregroundGrassBottom;
	FloatingSprite* foregroundGrassTop;
	cocos2d::Sprite* webs;
	cocos2d::Sprite* foregroundLight;

	cocos2d::ParticleSystem* windParticles;
	cocos2d::ParticleSystem* fireflyParticles;

	static MenuBackground* menuBackgroundInstance;
};
