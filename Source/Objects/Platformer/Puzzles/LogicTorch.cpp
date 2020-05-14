#include "LogicTorch.h"

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

const std::string LogicTorch::MapKey = "logic-torch";
const std::string LogicTorch::PropertyColor = "color";
const std::string LogicTorch::PropertyIsOn = "is-on";

LogicTorch* LogicTorch::create(ValueMap& properties)
{
	LogicTorch* instance = new LogicTorch(properties);

	instance->autorelease();

	return instance;
}

LogicTorch::LogicTorch(ValueMap& properties) : super(properties)
{
	this->torch = Sprite::create(ObjectResources::Puzzles_Torch_Torch);
	this->isOn = GameUtils::getKeyOrDefault(this->properties, LogicTorch::PropertyIsOn, Value(false)).asBool();

	std::string colorStr = GameUtils::getKeyOrDefault(this->properties, LogicTorch::PropertyColor, Value("")).asString();

	if (colorStr == "blue")
	{
		this->color = TorchColor::Blue;
		this->fire = SmartAnimationSequenceNode::create(FXResources::TorchFireBlue_TorchFire_0000);
		this->glow = Sprite::create(ObjectResources::Decor_Torch_TorchGlowBlue);
	}
	else if (colorStr == "green")
	{
		this->color = TorchColor::Green;
		this->fire = SmartAnimationSequenceNode::create(FXResources::TorchFireGreen_TorchFire_0000);
		this->glow = Sprite::create(ObjectResources::Decor_Torch_TorchGlowGreen);
	}
	else if (colorStr == "purple")
	{
		this->color = TorchColor::Purple;
		this->fire = SmartAnimationSequenceNode::create(FXResources::TorchFirePurple_TorchFire_0000);
		this->glow = Sprite::create(ObjectResources::Decor_Torch_TorchGlowPurple);
	}
	else
	{
		this->color = TorchColor::Red;
		this->fire = SmartAnimationSequenceNode::create(FXResources::TorchFire_TorchFire_0000);
		this->glow = Sprite::create(ObjectResources::Decor_Torch_TorchGlow);
	}

	this->fire->setScale(1.5f);

	this->addChild(this->glow);
	this->addChild(this->fire);
	this->addChild(this->torch);
}

LogicTorch::~LogicTorch()
{
}

void LogicTorch::onEnter()
{
	super::onEnter();

	this->updateLogicTorchVisibility();
}

void LogicTorch::initializePositions()
{
	super::initializePositions();

	this->fire->setPosition(Vec2(0.0f, 16.0f));
	this->glow->setPosition(Vec2(0.0f, 0.0f));
}

void LogicTorch::torchOn()
{
	if (this->isOn)
	{
		return;
	}

	this->isOn = true;

	this->updateLogicTorchVisibility();
}

void LogicTorch::torchOff()
{
	if (!this->isOn)
	{
		return;
	}

	this->isOn = false;

	this->updateLogicTorchVisibility();
}

void LogicTorch::updateLogicTorchVisibility()
{
	this->glow->stopAllActions();
	this->fire->stopAnimation();

	if (this->isOn)
	{
		switch (this->color)
		{
			case TorchColor::Green:
			{
				this->fire->playAnimationRepeat(FXResources::TorchFireGreen_TorchFire_0000, 0.05f);
				break;
			}
			case TorchColor::Blue:
			{
				this->fire->playAnimationRepeat(FXResources::TorchFireBlue_TorchFire_0000, 0.05f);
				break;
			}
			case TorchColor::Purple:
			{
				this->fire->playAnimationRepeat(FXResources::TorchFirePurple_TorchFire_0000, 0.05f);
				break;
			}
			default:
			case TorchColor::Red:
			{
				this->fire->playAnimationRepeat(FXResources::TorchFire_TorchFire_0000, 0.05f);
				break;
			}
		}

		this->glow->runAction(RepeatForever::create(Sequence::create(
			FadeTo::create(1.0f, 0),
			DelayTime::create(0.25f),
			FadeTo::create(1.0f, 255),
			DelayTime::create(0.25f),
			nullptr
		)));
	}
}
