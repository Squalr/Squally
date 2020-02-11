#include "TitleScreenBackground.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCParticleSystemQuad.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/UI/FloatingSprite.h"
#include "Engine/UI/InfiniteParallaxNode.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/EntityResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

TitleScreenBackground* TitleScreenBackground::create()
{
	TitleScreenBackground* instance = new TitleScreenBackground();

	instance->autorelease();

	return instance;
}

TitleScreenBackground::TitleScreenBackground()
{
	this->background = Sprite::create(UIResources::Menus_Backgrounds_ForestBackground);
	this->fog = InfiniteParallaxNode::create(UIResources::Menus_Backgrounds_Fog);
	this->foregroundFog = InfiniteParallaxNode::create(UIResources::Menus_Backgrounds_Fog);
	this->backgroundTrees = FloatingSprite::create(UIResources::Menus_Backgrounds_LightTrees, Vec2(-12.0f, 8.0f), Vec2(7.0f, 5.0f));
	this->backgroundVines = FloatingSprite::create(UIResources::Menus_Backgrounds_FarVines, Vec2(12.0f, -8.0f), Vec2(7.0f, 5.0f));
	this->midgroundTrees = FloatingSprite::create(UIResources::Menus_Backgrounds_MidgroundTrees, Vec2(8.0f, -8.0f), Vec2(7.0f, 5.0f));
	this->tree = Sprite::create(UIResources::Menus_Backgrounds_Tree);
	this->eyes1 = SmartAnimationSequenceNode::create();
	this->eyes2 = SmartAnimationSequenceNode::create();
	this->foregroundVines = FloatingSprite::create(UIResources::Menus_Backgrounds_Vines, Vec2(-24.0f, 0.0f), Vec2(7.0f, 5.0f));
	this->foregroundGrassBottom = FloatingSprite::create(UIResources::Menus_Backgrounds_BottomSoil, Vec2(-32.0f, 0.0f), Vec2(7.0f, 5.0f));
	this->foregroundGrassTop = FloatingSprite::create(UIResources::Menus_Backgrounds_TopLeaves, Vec2(-32.0f, 0.0f), Vec2(7.0f, 5.0f));
	this->foregroundLight = Sprite::create(UIResources::Menus_Backgrounds_Light);
	this->squally = SmartAnimationNode::create(EntityResources::Squally_Animations);
	this->leftEyeController = SmartAnimationSequenceNode::create();
	this->rightEyeController = SmartAnimationSequenceNode::create();
	this->slime = SmartAnimationSequenceNode::create(UIResources::Menus_TitleScreen_Slime_Slime_0000);

	this->squally->setFlippedX(true);
	this->squally->playAnimation("Idle", SmartAnimationNode::AnimationPlayMode::Repeat, 0.5f);
	this->mainhand = this->squally->getAnimationPart("mainhand");

	if (this->mainhand != nullptr)
	{
		this->mainhand->replaceSprite(ObjectResources::Items_Equipment_Weapons_Wands_WoodenWand);
		this->mainhand->setOffset(Vec2(0.0f, -16.0f));
	}

	this->leftEyeController->setVisible(false);
	this->rightEyeController->setVisible(false);

	this->eyes1->playAnimationAndReverseRepeat(UIResources::Menus_Backgrounds_EyesA_0000, 0.025f, 1.54f, 0.025f, 2.5f, true);
	this->eyes2->playAnimationAndReverseRepeat(UIResources::Menus_Backgrounds_EyesB_0000, 0.025f, 1.25f, 0.025f, 3.25f, true);

	this->windParticles = ParticleSystemQuad::create(ParticleResources::Wind);
	this->fireflyParticles = ParticleSystemQuad::create(ParticleResources::Fireflies2);

	this->addChild(this->background);
	this->addChild(this->backgroundTrees);
	this->addChild(this->backgroundVines);
	this->addChild(this->midgroundTrees);
	this->addChild(this->fog);
	this->addChild(this->foregroundVines);
	this->addChild(this->tree);
	this->addChild(this->eyes1);
	this->addChild(this->eyes2);
	this->addChild(this->slime);
	this->addChild(this->squally);
	this->addChild(this->leftEyeController);
	this->addChild(this->rightEyeController);
	this->addChild(this->fireflyParticles);
	this->addChild(this->windParticles);
	this->addChild(this->foregroundFog);
	this->addChild(this->foregroundGrassBottom);
	this->addChild(this->foregroundGrassTop);
	this->addChild(this->foregroundLight);
}

TitleScreenBackground::~TitleScreenBackground()
{
}

void TitleScreenBackground::onEnter()
{
	super::onEnter();

	// Initialize particles to an intermediate state
	GameUtils::accelerateParticles(this->fireflyParticles, 2.0f);
	GameUtils::accelerateParticles(this->windParticles, 5.0f);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 base = Vec2(visibleSize.width / 2 + 228.0f, visibleSize.height / 2 + 160.0f);

	const float floatSpeed = 3.0f;
	const float floatSpeedPostSink = 1.25f;
	const float sinkSpeed = 6.0f;
	const float floatDelta = 64.0f;
	const float floatDeltaPostSink = 8.0f;
	const float sinkOffset = 462.0f;

	FiniteTimeAction* bounceDown = EaseSineInOut::create(MoveTo::create(floatSpeed, Vec2(base.x, base.y - floatDelta)));
	FiniteTimeAction* bounceUp = EaseSineInOut::create(MoveTo::create(floatSpeed, Vec2(base.x, base.y)));
	FiniteTimeAction* sinkDown = EaseSineInOut::create(MoveTo::create(sinkSpeed, Vec2(base.x, base.y - sinkOffset)));
	FiniteTimeAction* bounceUpPostSink = EaseSineInOut::create(MoveTo::create(floatSpeedPostSink, Vec2(base.x, base.y - sinkOffset + floatDeltaPostSink)));
	FiniteTimeAction* bounceDownPostSink = EaseSineInOut::create(MoveTo::create(floatSpeedPostSink, Vec2(base.x, base.y - sinkOffset)));
	FiniteTimeAction* sinkUp = EaseSineInOut::create(MoveTo::create(sinkSpeed, Vec2(base.x, base.y)));

	CallFunc* pokeSlime = CallFunc::create([=]
	{
		this->squally->playAnimation("AttackStabLite", SmartAnimationNode::AnimationPlayMode::ReturnToIdle,  1.0f);
		this->slime->playAnimation(UIResources::Menus_TitleScreen_Slime_Slime_0000, 0.035f);
	});
	
	this->squally->stopAllActions();
	this->squally->runAction(RepeatForever::create(
		Sequence::create(
			bounceDown,
			bounceUp,
			bounceDown,
			bounceUp,
			bounceDown,
			bounceUp,
			sinkDown,
			pokeSlime,
			DelayTime::create(0.4f),
			bounceUpPostSink,
			bounceDownPostSink,
			pokeSlime,
			DelayTime::create(0.4f),
			sinkUp,
			bounceDown,
			bounceUp,
			bounceDown,
			bounceUp,
			bounceDown,
			bounceUp,
			nullptr
		))
	);
	this->runEyeBlinkLoop();

	this->fog->stopAllActions();
	this->foregroundFog->stopAllActions();

	this->fog->runAction(RepeatForever::create(MoveBy::create(2.0f, Vec2(-92.0f, 0))));
	this->foregroundFog->runAction(RepeatForever::create(MoveBy::create(2.0f, Vec2(-196.0f, 0))));
}

void TitleScreenBackground::initializeListeners()
{
	super::initializeListeners();
}

void TitleScreenBackground::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->backgroundTrees->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->backgroundVines->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height - 320.0f));
	this->midgroundTrees->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->tree->setPosition(Vec2(visibleSize.width / 2.0f + 38.0f, visibleSize.height / 2.0f + 180.0f));

	this->eyes1->setPosition(Vec2(visibleSize.width / 2.0f + 48.0f, visibleSize.height / 2.0f - 180.0f));
	this->eyes2->setPosition(Vec2(visibleSize.width / 2.0f + 48.0f, visibleSize.height / 2.0f - 180.0f));
	this->fog->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 120.0f));
	this->foregroundFog->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 256.0f));
	this->foregroundVines->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height - 196.0f));
	this->foregroundGrassBottom->setPosition(Vec2(visibleSize.width / 2.0f, 0.0f));
	this->foregroundGrassTop->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height - 32.0f));
	this->foregroundLight->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height - foregroundLight->getContentSize().height / 2.0f));
	this->windParticles->setPosition(Vec2(visibleSize.width, visibleSize.height / 2.0f));
	this->fireflyParticles->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->slime->setPosition(Vec2(visibleSize.width / 2.0f + 112.0f, visibleSize.height / 2.0f - 320.0f));
	this->squally->setPosition(Vec2(visibleSize.width / 2.0f + 228.0f, visibleSize.height / 2.0f + 160.0f));
}

void TitleScreenBackground::runEyeBlinkLoop()
{
	const float BlinkSpeed = 0.0075f;
	const float EyesClosedDuration = 0.015f;
	const float TimeBetweenBlinks = 5.5f;
	
	this->leftEyeController->playAnimationAndReverseRepeat(EntityResources::Squally_Blink_EYE_L_Blink_0000, BlinkSpeed, EyesClosedDuration, BlinkSpeed, TimeBetweenBlinks);
	this->leftEyeController->getForwardsAnimation()->onSpriteChange = [=](std::string spriteResource)
	{
		AnimationPart* leftEye = this->squally->getAnimationPart("eye_left");
		
		if (leftEye != nullptr)
		{
			leftEye->replaceSprite(spriteResource);
		}
	};
	this->leftEyeController->getBackwardsAnimation()->onSpriteChange = [=](std::string spriteResource)
	{
		AnimationPart* leftEye = this->squally->getAnimationPart("eye_left");
		
		if (leftEye != nullptr)
		{
			leftEye->replaceSprite(spriteResource);
		}
	};
	this->rightEyeController->playAnimationAndReverseRepeat(EntityResources::Squally_Blink_EYE_L_Blink_0000, BlinkSpeed, EyesClosedDuration, BlinkSpeed, TimeBetweenBlinks);
	this->rightEyeController->getForwardsAnimation()->onSpriteChange = [=](std::string spriteResource)
	{
		AnimationPart* rightEye = this->squally->getAnimationPart("eye_right");
		
		if (rightEye != nullptr)
		{
			rightEye->replaceSprite(spriteResource);
		}
	};
	this->rightEyeController->getBackwardsAnimation()->onSpriteChange = [=](std::string spriteResource)
	{
		AnimationPart* rightEye = this->squally->getAnimationPart("eye_right");
		
		if (rightEye != nullptr)
		{
			rightEye->replaceSprite(spriteResource);
		}
	};
}
