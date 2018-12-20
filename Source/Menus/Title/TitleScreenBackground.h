#pragma once

#include "Engine/SmartNode.h"

class InfiniteParallaxNode;
class FloatingSprite;
class MenuSprite;
class SmartAnimationNode;
class SmartAnimationSequenceNode;

namespace cocos2d
{
	class Sprite;
	class ParticleSystem;
}

class TitleScreenBackground : public SmartNode
{
public:
	static TitleScreenBackground* create();

private:
	TitleScreenBackground();
	~TitleScreenBackground();

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

	SmartAnimationNode* squally;
	SmartAnimationSequenceNode* slime;
	cocos2d::Sprite* background;
	FloatingSprite* backgroundVines;
	FloatingSprite* backgroundTrees;
	FloatingSprite* midgroundTrees;
	cocos2d::Sprite* tree;
	SmartAnimationSequenceNode* eyes1;
	SmartAnimationSequenceNode* eyes2;
	FloatingSprite* foregroundVines;
	InfiniteParallaxNode* fog;
	InfiniteParallaxNode* foregroundFog;
	FloatingSprite* foregroundGrassBottom;
	FloatingSprite* foregroundGrassTop;
	cocos2d::Sprite* foregroundLight;

	cocos2d::ParticleSystem* windParticles;
	cocos2d::ParticleSystem* fireflyParticles;
};
