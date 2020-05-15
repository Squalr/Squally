#include "LogicTorch.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string LogicTorch::MapKey = "logic-torch";
const std::string LogicTorch::PropertyColor = "color";
const std::string LogicTorch::PropertyIsOn = "is-on";
const std::string LogicTorch::PropertyIsInteractable = "interactable";
const std::string LogicTorch::PropertySaveKey = "save-key";
const std::string LogicTorch::EventTorchLogicSwitchPrefix = "EVENT_OBJECT_TORCH_LOGIC_SWITCH_CHANGED_";

LogicTorch* LogicTorch::create(ValueMap& properties)
{
	LogicTorch* instance = new LogicTorch(properties);

	instance->autorelease();

	return instance;
}

LogicTorch::LogicTorch(ValueMap& properties) : super(properties, InteractType::None, Size(101.0f, 111.0f))
{
	this->torch = Sprite::create(ObjectResources::Puzzles_Torch_Torch);
	this->fire = SmartAnimationSequenceNode::create();
	this->isOn = GameUtils::getKeyOrDefault(this->properties, LogicTorch::PropertyIsOn, Value(false)).asBool();
	this->saveKey = GameUtils::getKeyOrDefault(this->properties, LogicTorch::PropertySaveKey, Value("")).asString();

	std::string colorStr = GameUtils::getKeyOrDefault(this->properties, LogicTorch::PropertyColor, Value("")).asString();

	if (GameUtils::getKeyOrDefault(this->properties, LogicTorch::PropertyIsInteractable, Value(false)).asBool())
	{
		this->setInteractType(InteractType::Input);
	}

	if (colorStr == "blue")
	{
		this->color = TorchColor::Blue;
		this->glow = Sprite::create(ObjectResources::Decor_Torch_TorchGlowBlue);
	}
	else if (colorStr == "green")
	{
		this->color = TorchColor::Green;
		this->glow = Sprite::create(ObjectResources::Decor_Torch_TorchGlowGreen);
	}
	else if (colorStr == "purple")
	{
		this->color = TorchColor::Purple;
		this->glow = Sprite::create(ObjectResources::Decor_Torch_TorchGlowPurple);
	}
	else
	{
		colorStr = "red";
		this->color = TorchColor::Red;
		this->glow = Sprite::create(ObjectResources::Decor_Torch_TorchGlow);
	}

	this->addTag(colorStr);

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

	if (!this->saveKey.empty())
	{
		this->isOn = SaveManager::getProfileDataOrDefault(this->saveKey, Value(this->isOn)).asBool();

		this->listenForMapEvent(LogicTorch::EventTorchLogicSwitchPrefix + this->saveKey, [=](ValueMap)
		{
			this->isOn = SaveManager::getProfileDataOrDefault(this->saveKey, Value(this->isOn)).asBool();
			
			this->updateLogicTorchVisibility();
		});
	}

	this->updateLogicTorchVisibility();
}

void LogicTorch::initializePositions()
{
	super::initializePositions();

	this->fire->setPosition(Vec2(0.0f, 16.0f));
	this->glow->setPosition(Vec2(0.0f, 0.0f));
}

void LogicTorch::onInteract()
{
	if (this->isOn)
	{
		this->torchOff();
	}
	else
	{
		this->torchOn();
	}

	if (!this->saveKey.empty())
	{
		SaveManager::SaveProfileData(this->saveKey, Value(this->isOn));

		this->broadcastMapEvent(LogicTorch::EventTorchLogicSwitchPrefix + this->saveKey, ValueMap());
	}
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

	this->glow->setVisible(this->isOn);
	this->fire->setVisible(this->isOn);

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
