#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class AnimationPart;
class FloatingSprite;
class InfiniteScrollSprite;
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

	SmartAnimationNode* squally = nullptr;
	SmartAnimationSequenceNode* leftEyeController = nullptr;
	SmartAnimationSequenceNode* rightEyeController = nullptr;
	AnimationPart* mainhand = nullptr;
	SmartAnimationSequenceNode* slime = nullptr;
	cocos2d::Sprite* background = nullptr;
	FloatingSprite* backgroundVines = nullptr;
	FloatingSprite* backgroundTrees = nullptr;
	FloatingSprite* midgroundTrees = nullptr;
	cocos2d::Sprite* tree = nullptr;
	SmartAnimationSequenceNode* eyes1 = nullptr;
	SmartAnimationSequenceNode* eyes2 = nullptr;
	FloatingSprite* foregroundVines = nullptr;
	InfiniteScrollSprite* fog = nullptr;
	InfiniteScrollSprite* foregroundFog = nullptr;
	FloatingSprite* foregroundGrassBottom = nullptr;
	FloatingSprite* foregroundGrassTop = nullptr;
	cocos2d::Sprite* foregroundLight = nullptr;

	SmartParticles* windParticles = nullptr;
	SmartParticles* fireflyParticles = nullptr;
};
