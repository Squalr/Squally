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

Torch::Torch(ValueMap& properties) : super(properties)
{
	this->torch = Sprite::create(ObjectResources::Decor_Torch);
	this->glow = Sprite::create(ObjectResources::Decor_TorchGlow);
	this->fire = SmartAnimationSequenceNode::create(FXResources::TorchFire_TorchFire_0000);
	this->isOn = false;
	this->isCulled = false;

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

	this->torchOn();
}

void Torch::initializePositions()
{
	super::initializePositions();

	this->fire->setPosition(Vec2(0.0f, 80.0f));
	this->glow->setPosition(Vec2(0.0f, 56.0f));
}

void Torch::torchOn()
{
	if (this->isOn)
	{
		return;
	}

	this->isOn = true;

	this->updateTorchVisibility();
}

void Torch::torchOff()
{
	if (!this->isOn)
	{
		return;
	}

	this->isOn = false;

	this->updateTorchVisibility();
}

void Torch::updateTorchVisibility()
{
	this->glow->stopAllActions();
	this->fire->stopAnimation();

	if (this->isOn && !this->isCulled)
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
}

void Torch::optimizationHideOffscreenTorch()
{
	float zoom = GameCamera::getInstance()->getCameraZoomOnTarget(this);
	Size clipSize = (Director::getInstance()->getVisibleSize()) * zoom;
	Rect cameraRect = Rect(GameCamera::getInstance()->getCameraPosition() - Vec2(clipSize.width / 2.0f, clipSize.height / 2.0f), clipSize);
	Rect thisRect = Rect(GameUtils::getWorldCoords(this), Size(128.0f, 128.0f));

	bool isNotOnScreen = !cameraRect.intersectsRect(thisRect);

	if (this->isCulled != isNotOnScreen)
	{
		this->isCulled = isNotOnScreen;

		this->updateTorchVisibility();
	}
}
