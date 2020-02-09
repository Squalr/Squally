#include "Torch.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string Torch::MapKeyTorch = "torch";

Torch* Torch::create(ValueMap& properties)
{
	Torch* instance = new Torch(properties);

	instance->autorelease();

	return instance;
}

Torch::Torch(ValueMap& properties) : super(properties)
{
	this->torch = Sprite::create(ObjectResources::Decor_Torch);
	this->glow = Sprite::create(ObjectResources::Decor_TorchGlow);
	this->fire = SmartAnimationSequenceNode::create(FXResources::TorchFire_TorchFire_0000);

	this->fire->setScale(1.5f);

	this->addChild(this->glow);
	this->addChild(this->torch);
	this->addChild(this->fire);
}

Torch::~Torch()
{
}

void Torch::onEnter()
{
	super::onEnter();

	this->fire->playAnimationRepeat(FXResources::TorchFire_TorchFire_0000, 0.05f);

	this->glow->runAction(RepeatForever::create(Sequence::create(
		FadeTo::create(1.0f, 0),
		DelayTime::create(0.25f),
		FadeTo::create(1.0f, 255),
		DelayTime::create(0.25f),
		nullptr
	)));
}

void Torch::initializePositions()
{
	super::initializePositions();

	this->fire->setPosition(Vec2(0.0f, 80.0f));
	this->glow->setPosition(Vec2(0.0f, 56.0f));
}
