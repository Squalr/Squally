#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class ParticleSystem;
	class Sprite;
}

class InfiniteParallaxNode;
class FloatingSprite;
class SmartParticles;

class MenuBackground : public SmartNode
{
public:
	static MenuBackground* claimInstance();
	static MenuBackground* getInstance();

protected:
	MenuBackground();
	virtual ~MenuBackground();

	void initializePositions() override;

private:
	typedef SmartNode super;

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

	SmartParticles* windParticles;
	SmartParticles* fireflyParticles;

	static MenuBackground* menuBackgroundInstance;
};
