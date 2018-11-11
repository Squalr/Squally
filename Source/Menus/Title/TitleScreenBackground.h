#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"

#include "Engine/SmartNode.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/FloatingSprite.h"
#include "Engine/UI/InfiniteParallaxNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"

using namespace cocos2d;
using namespace cocos_experimental;

class TitleScreenBackground : public SmartNode
{
public:
	static TitleScreenBackground * create();

private:
	TitleScreenBackground();
	~TitleScreenBackground();

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;
	void createSlimeAnimation();

	Node* squallyNode;
	AnimationNode* squally;
	SpriterEngine::EntityInstance* squallyEntity;
	Node* slimeNode;
	Sprite* slime;
	Animation* slimeAnimation;
	Sprite* background;
	FloatingSprite* backgroundVines;
	FloatingSprite* backgroundTrees;
	FloatingSprite* midgroundTrees;
	Sprite* tree;
	Animation* eyes1Anim;
	Animation* eyes2Anim;
	Sprite* eyes1;
	Sprite* eyes2;
	FloatingSprite* foregroundVines;
	InfiniteParallaxNode* fog;
	InfiniteParallaxNode* foregroundFog;
	FloatingSprite* foregroundGrassBottom;
	FloatingSprite* foregroundGrassTop;
	Sprite* foregroundLight;

	ParticleSystem* windParticles;
	ParticleSystem* fireflyParticles;
};
