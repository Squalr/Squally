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
const std::string LogicTorch::PropertyOperation = "operation";
const std::string LogicTorch::PropertyIsOn = "is-on";
const std::string LogicTorch::PropertyIsInteractable = "interactable";
const std::string LogicTorch::PropertySaveKey = "save-key";
const std::string LogicTorch::MapEventTorchLogicSwitchSavePrefix = "torch-logic-switched-by-save-";
const std::string LogicTorch::MapEventTorchLogicSwitchPrefix = "torch-logic-switched";
const std::string LogicTorch::MapEventSolveTorches = "solve-torches";
const std::string LogicTorch::MapEventCheckComplete = "check-complete";
const std::string LogicTorch::SaveKeyIsSolved = "SAVE_KEY_IS_SOLVED";

LogicTorch* LogicTorch::create(ValueMap& properties)
{
	LogicTorch* instance = new LogicTorch(properties);

	instance->autorelease();

	return instance;
}

LogicTorch::LogicTorch(ValueMap& properties) : super(properties, InteractType::None, Size(101.0f, 111.0f))
{
	this->colorName = GameUtils::getKeyOrDefault(this->properties, LogicTorch::PropertyColor, Value("")).asString();
	this->operationName = GameUtils::getKeyOrDefault(this->properties, LogicTorch::PropertyOperation, Value("")).asString();
	this->torch = Sprite::create(ObjectResources::Puzzles_Torch_Torch);
	this->fire = SmartAnimationSequenceNode::create();
	this->isOn = GameUtils::getKeyOrDefault(this->properties, LogicTorch::PropertyIsOn, Value(false)).asBool();
	this->saveKey = GameUtils::getKeyOrDefault(this->properties, LogicTorch::PropertySaveKey, Value("")).asString();
	this->color = LogicTorch::StrToColor(this->colorName);
	this->operation = LogicTorch::StrToOperation(this->operationName);

	switch (this->color)
	{
		case TorchColor::Green:
		{
			this->glow = Sprite::create(ObjectResources::Decor_Torch_TorchGlowGreen);
			break;
		}
		case TorchColor::Blue:
		{
			this->glow = Sprite::create(ObjectResources::Decor_Torch_TorchGlowBlue);
			break;
		}
		case TorchColor::Purple:
		{
			this->glow = Sprite::create(ObjectResources::Decor_Torch_TorchGlowPurple);
			break;
		}
		default:
		case TorchColor::Red:
		{
			this->glow = Sprite::create(ObjectResources::Decor_Torch_TorchGlow);
			break;
		}
	}

	this->addTag(this->operationName + "_" + this->colorName);

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
	
	this->isOn |= this->isSolved();

	// Listen for events if unsolved
	if (!this->isSolved() && !this->saveKey.empty())
	{
		this->isOn = SaveManager::getProfileDataOrDefault(this->saveKey, Value(this->isOn)).asBool();

		this->listenForMapEvent(LogicTorch::MapEventTorchLogicSwitchSavePrefix + this->saveKey, [=](ValueMap)
		{
			this->isOn = SaveManager::getProfileDataOrDefault(this->saveKey, Value(this->isOn)).asBool();
			
			this->updateLogicTorchVisibility();
		});

		// For torches with a save key, use a different mode to save! Allows cross map syncing.
		this->listenForMapEvent(LogicTorch::MapEventSolveTorches, [=](ValueMap)
		{
			SaveManager::SoftSaveProfileData(this->saveKey + "_" + LogicTorch::SaveKeyIsSolved, Value(true));
			this->setInteractType(InteractType::None);
			this->torchOn();
		});

		SaveManager::SoftSaveProfileData(this->saveKey, Value(this->isOn));
	}
	else if (!this->isSolved() && this->saveKey.empty())
	{
		// For torches with no save key, save as object state
		this->listenForMapEvent(LogicTorch::MapEventSolveTorches, [=](ValueMap)
		{
			this->saveObjectState(LogicTorch::SaveKeyIsSolved, Value(true));
			this->setInteractType(InteractType::None);
			this->torchOn();
		});
	}

	// Set interactable if unsolved
	if (!this->isSolved() && GameUtils::getKeyOrDefault(this->properties, LogicTorch::PropertyIsInteractable, Value(false)).asBool())
	{
		this->setInteractType(InteractType::Input);
	}

	this->updateLogicTorchVisibility();
}

void LogicTorch::initializePositions()
{
	super::initializePositions();

	this->fire->setPosition(Vec2(0.0f, 16.0f));
	this->glow->setPosition(Vec2(0.0f, 0.0f));
}

LogicTorch::TorchColor LogicTorch::StrToColor(std::string colorName)
{
	if (colorName == "blue")
	{
		return TorchColor::Blue;
	}
	else if (colorName == "green")
	{
		return TorchColor::Green;
	}
	else if (colorName == "purple")
	{
		return TorchColor::Purple;
	}
	else
	{
		return TorchColor::Red;
	}
}

LogicTorch::Operation LogicTorch::StrToOperation(std::string operationName)
{
	if (operationName == "and")
	{
		return Operation::And;
	}
	else if (operationName == "or")
	{
		return Operation::Or;
	}
	else if (operationName == "xor")
	{
		return Operation::Xor;
	}

	return Operation::None;
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
		SaveManager::SoftSaveProfileData(this->saveKey, Value(this->isOn));

		this->broadcastMapEvent(LogicTorch::MapEventTorchLogicSwitchSavePrefix + this->saveKey, ValueMap());
		this->broadcastMapEvent(LogicTorch::MapEventTorchLogicSwitchPrefix + this->colorName, ValueMap());
	}

	this->broadcastMapEvent(LogicTorch::MapEventCheckComplete, ValueMap());
}

bool LogicTorch::isTorchOn()
{
	return this->isOn;
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

bool LogicTorch::isSolved()
{
	if (this->saveKey.empty())
	{
		return this->loadObjectStateOrDefault(LogicTorch::SaveKeyIsSolved, Value(false)).asBool();
	}
	else
	{
		return SaveManager::getProfileDataOrDefault(this->saveKey + "_" + LogicTorch::SaveKeyIsSolved, Value(false)).asBool();
	}
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
