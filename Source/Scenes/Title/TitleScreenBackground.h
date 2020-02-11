#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class AnimationPart;
class ClickableNode;
class FloatingSprite;
class InfiniteParallaxNode;
class SmartAnimationNode;
class SmartAnimationSequenceNode;
class SmartParticles;

class TitleScreenBackground : public SmartNode
{
public:
	static TitleScreenBackground* create();

protected:
	TitleScreenBackground();
	virtual ~TitleScreenBackground();

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

private:
	typedef SmartNode super;
	
	void runEyeBlinkLoop();

	SmartAnimationNode* squally;
	SmartAnimationSequenceNode* leftEyeController;
	SmartAnimationSequenceNode* rightEyeController;
	AnimationPart* mainhand;
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

	SmartParticles* windParticles;
	SmartParticles* fireflyParticles;
};
