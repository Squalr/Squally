#include "Torch.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string Torch::MapKey = "torch";

Torch* Torch::create(ValueMap& properties)
{
	Torch* instance = new Torch(properties);

	instance->autorelease();

	return instance;
}

Torch::Torch(ValueMap& properties) : super(
	properties,
	InteractObject::InteractType::None,
	Size(48.0f, 128.0f))
{
	this->torch = Sprite::create(ObjectResources::Decor_Torch_Torch);
	this->glow = Sprite::create(ObjectResources::Decor_Torch_TorchGlow);
	this->fire = SmartAnimationSequenceNode::create(FXResources::TorchFire_TorchFire_0000);

	this->fire->setScale(1.5f);
	this->setContentSize(Size(128.0f, 128.0f));

	this->backOnNode->addChild(this->glow);
	this->backNode->addChild(this->torch);
	this->onNode->addChild(this->fire);
}

Torch::~Torch()
{
}

void Torch::onEnter()
{
	super::onEnter();
}

void Torch::initializePositions()
{
	super::initializePositions();

	this->fire->setPosition(Vec2(0.0f, 80.0f));
	this->glow->setPosition(Vec2(0.0f, 56.0f));
}

void Torch::onEnable(bool isInit, bool isInstant)
{
	super::onEnable(isInit, isInstant);
	
	this->startFx();
}

void Torch::onDisable(bool isInit, bool isInstant)
{
	super::onDisable(isInit, isInstant);

	this->stopFx();
}

void Torch::onOptimizationHide()
{
	super::onOptimizationHide();
	
	this->stopFx();
}

void Torch::onOptimizationShow()
{
	super::onOptimizationShow();

	if (this->isOn())
	{
		this->startFx();
	}
}

void Torch::startFx()
{
	this->fire->playAnimationRepeat(FXResources::TorchFire_TorchFire_0000, 0.05f);

	this->glow->runAction(RepeatForever::create(Sequence::create(
		FadeTo::create(1.0f, 0),
		DelayTime::create(0.25f),
		FadeTo::create(1.0f, 255),
		DelayTime::create(0.25f),
		nullptr
	)));
}

void Torch::stopFx()
{
	this->glow->stopAllActions();
	this->fire->stopAnimation();
}
