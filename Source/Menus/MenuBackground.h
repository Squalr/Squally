#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class InfiniteScrollSprite;
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

	cocos2d::Sprite* background = nullptr;
	FloatingSprite* backgroundTrees = nullptr;
	FloatingSprite* midgroundTrees = nullptr;
	FloatingSprite* foregroundVines = nullptr;
	InfiniteScrollSprite* fog = nullptr;
	InfiniteScrollSprite* foregroundFog = nullptr;
	FloatingSprite* foregroundGrassBottom = nullptr;
	FloatingSprite* foregroundGrassTop = nullptr;
	cocos2d::Sprite* webs = nullptr;
	cocos2d::Sprite* foregroundLight = nullptr;

	SmartParticles* windParticles = nullptr;
	SmartParticles* fireflyParticles = nullptr;

	static MenuBackground* menuBackgroundInstance;
};
