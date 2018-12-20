#include "SmartAnimationSequenceNode.h"

#include "cocos/2d/CCAnimation.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Utils/GameUtils.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

SmartAnimationSequenceNode* SmartAnimationSequenceNode::create(std::string defaultSprite)
{
	SmartAnimationSequenceNode* instance = new SmartAnimationSequenceNode(defaultSprite);

	instance->autorelease();

	return instance;
}

SmartAnimationSequenceNode* SmartAnimationSequenceNode::create()
{
	SmartAnimationSequenceNode* instance = new SmartAnimationSequenceNode();

	instance->autorelease();

	return instance;
}

SmartAnimationSequenceNode::SmartAnimationSequenceNode(std::string defaultSprite)
{
	this->sprite = Sprite::create(defaultSprite);

	this->addChild(this->sprite);
}

SmartAnimationSequenceNode::SmartAnimationSequenceNode()
{
	this->sprite = Sprite::create();

	this->addChild(this->sprite);
}

SmartAnimationSequenceNode::~SmartAnimationSequenceNode()
{
}

void SmartAnimationSequenceNode::playAnimation(std::string initialSequenceResourceFile, float animationSpeed, std::function<void()> onAnimationComplete)
{
	Animation* animation = Animation::create();
	auto animationFiles = GameUtils::getAllAnimationFiles(initialSequenceResourceFile);

	for (auto it = animationFiles.begin(); it != animationFiles.end(); it++)
	{
		animation->addSpriteFrameWithFile(*it);
	}

	animation->addSpriteFrameWithFile(UIResources::EmptyImage);

	animation->setDelayPerUnit(animationSpeed);

	this->sprite->runAction(Sequence::create(
		Animate::create(animation),
		CallFunc::create([=]()
		{
			if (onAnimationComplete != nullptr)
			{
				onAnimationComplete();
			}
		}),
		nullptr
	));
}

void SmartAnimationSequenceNode::playAnimationRepeat(std::string initialSequenceResourceFile, float animationSpeed, float repeatDelay)
{
	Animation* animation = Animation::create();
	auto animationFiles = GameUtils::getAllAnimationFiles(initialSequenceResourceFile);

	for (auto it = animationFiles.begin(); it != animationFiles.end(); it++)
	{
		animation->addSpriteFrameWithFile(*it);
	}

	animation->addSpriteFrameWithFile(UIResources::EmptyImage);

	animation->setDelayPerUnit(animationSpeed);
	this->sprite->runAction(RepeatForever::create(Sequence::create(Animate::create(animation), DelayTime::create(repeatDelay), nullptr)));
}

void SmartAnimationSequenceNode::playAnimationAndReverse(std::string initialSequenceResourceFile, float animationSpeedIn, float reverseDelay, float animationSpeedOut, std::function<void()> onAnimationComplete)
{
	Animation* animationIn = Animation::create();
	Animation* animationOut = Animation::create();
	auto animationFiles = GameUtils::getAllAnimationFiles(initialSequenceResourceFile);

	animationOut->addSpriteFrameWithFile(UIResources::EmptyImage);

	for (auto it = animationFiles.begin(); it != animationFiles.end(); it++)
	{
		animationIn->addSpriteFrameWithFile(*it);
		animationOut->addSpriteFrameWithFile(*it);
	}

	animationIn->addSpriteFrameWithFile(UIResources::EmptyImage);

	animationIn->setDelayPerUnit(animationSpeedIn);
	animationOut->setDelayPerUnit(animationSpeedOut);

	this->sprite->runAction(Sequence::create(
		Animate::create(animationIn),
		DelayTime::create(reverseDelay),
		Animate::create(animationOut)->reverse(),
		CallFunc::create([=]()
		{
			if (onAnimationComplete != nullptr)
			{
				onAnimationComplete();
			}
		}),
		nullptr
	));
}

void SmartAnimationSequenceNode::playAnimationAndReverseRepeat(std::string initialSequenceResourceFile, float animationSpeedIn, float reverseDelay, float animationSpeedOut, float repeatDelay)
{
	Animation* animationIn = Animation::create();
	Animation* animationOut = Animation::create();
	auto animationFiles = GameUtils::getAllAnimationFiles(initialSequenceResourceFile);

	animationOut->addSpriteFrameWithFile(UIResources::EmptyImage);

	for (auto it = animationFiles.begin(); it != animationFiles.end(); it++)
	{
		animationIn->addSpriteFrameWithFile(*it);
		animationOut->addSpriteFrameWithFile(*it);
	}

	animationIn->addSpriteFrameWithFile(UIResources::EmptyImage);

	animationIn->setDelayPerUnit(animationSpeedIn);
	animationOut->setDelayPerUnit(animationSpeedOut);

	this->sprite->runAction(RepeatForever::create(Sequence::create(Animate::create(animationIn), DelayTime::create(reverseDelay), Animate::create(animationOut)->reverse(), DelayTime::create(repeatDelay), nullptr)));
}
