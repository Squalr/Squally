#include "Brazier.h"

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
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string Brazier::MapKey = "logic-torch";
const std::string Brazier::PropertyColor = "color";
const std::string Brazier::PropertyOperation = "operation";
const std::string Brazier::PropertySaveKey = "save-key";
const std::string Brazier::MapEventTorchLogicSwitchSavePrefix = "torch-logic-switched-by-save-";
const std::string Brazier::MapEventTorchLogicSwitchPrefix = "torch-logic-switched";
const std::string Brazier::MapEventSolveTorches = "solve-torches";
const std::string Brazier::MapEventCheckComplete = "check-complete";
const std::string Brazier::SaveKeyIsSolved = "SAVE_KEY_IS_SOLVED";

Brazier* Brazier::create(ValueMap& properties)
{
	Brazier* instance = new Brazier(properties);

	instance->autorelease();

	return instance;
}

Brazier::Brazier(ValueMap& properties) : super(properties, InteractType::None, Size(101.0f, 111.0f))
{
	this->colorName = GameUtils::getKeyOrDefault(this->properties, Brazier::PropertyColor, Value("")).asString();
	this->operationName = GameUtils::getKeyOrDefault(this->properties, Brazier::PropertyOperation, Value("")).asString();
	this->torch = Sprite::create(ObjectResources::Puzzles_Torch_Torch);
	this->fire = SmartAnimationSequenceNode::create();
	this->saveKey = GameUtils::getKeyOrDefault(this->properties, Brazier::PropertySaveKey, Value("")).asString();
	this->color = Brazier::StrToColor(this->colorName);
	this->operation = Brazier::StrToOperation(this->operationName);
	this->burnSound = WorldSound::create(SoundResources::Platformer_FX_Fire_FireSizzle1);
	this->onSound = WorldSound::create(SoundResources::Platformer_FX_Woosh_WooshFire2);
	this->offSound = WorldSound::create(SoundResources::Platformer_FX_Woosh_Woosh1);
	this->interactSound = WorldSound::create(SoundResources::Platformer_Objects_Machines_LampClick);

	this->onSound->setCustomMultiplier(0.25f);
	this->offSound->setCustomMultiplier(0.25f);

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

	this->backOnNode->addChild(this->glow);
	this->onNode->addChild(this->fire);
	this->frontNode->addChild(this->torch);
	this->addChild(this->burnSound);
	this->addChild(this->onSound);
	this->addChild(this->offSound);
	this->addChild(this->interactSound);
}

Brazier::~Brazier()
{
}

void Brazier::onEnter()
{
	super::onEnter();
	
	/*
	this->isOn |= this->isSolved();

	static float TorchDelay = 0.0f;

	TorchDelay = 0.0f;

	// Listen for events if unsolved
	if (!this->isSolved() && !this->saveKey.empty())
	{
		this->isOn = SaveManager::GetProfileDataOrDefault(this->saveKey, Value(this->isOn)).asBool();

		this->listenForMapEvent(Brazier::MapEventTorchLogicSwitchSavePrefix + this->saveKey, [=](ValueMap)
		{
			this->isOn = SaveManager::GetProfileDataOrDefault(this->saveKey, Value(this->isOn)).asBool();
			
			this->updateBrazierVisibility();
		});

		// For torches with a save key, use a different mode to save! Allows cross map syncing.
		this->listenForMapEvent(Brazier::MapEventSolveTorches, [=](ValueMap)
		{
			SaveManager::SoftSaveProfileData(this->saveKey + "_" + Brazier::SaveKeyIsSolved, Value(true));
			this->setInteractType(InteractType::None);

			TorchDelay += 0.1f;

			this->runAction(Sequence::create(
				DelayTime::create(TorchDelay),
				CallFunc::create([=]()
				{
					this->torchOn();
				}),
				nullptr
			));
		});

		SaveManager::SoftSaveProfileData(this->saveKey, Value(this->isOn));
	}
	else if (!this->isSolved() && this->saveKey.empty())
	{
		// For torches with no save key, save as object state
		this->listenForMapEvent(Brazier::MapEventSolveTorches, [=](ValueMap)
		{
			this->saveObjectState(Brazier::SaveKeyIsSolved, Value(true));
			this->setInteractType(InteractType::None);

			TorchDelay += 0.1f;

			this->runAction(Sequence::create(
				DelayTime::create(TorchDelay),
				CallFunc::create([=]()
				{
					this->torchOn();
				}),
				nullptr
			));
		});
	}

	// Set interactable if unsolved
	if (!this->isSolved() && GameUtils::getKeyOrDefault(this->properties, Brazier::PropertyIsInteractable, Value(false)).asBool())
	{
		this->setInteractType(InteractType::Input);
	}
	*/
}

void Brazier::initializePositions()
{
	super::initializePositions();

	this->fire->setPosition(Vec2(0.0f, 16.0f));
	this->glow->setPosition(Vec2(0.0f, 0.0f));
}

Brazier::TorchColor Brazier::StrToColor(std::string colorName)
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

Brazier::Operation Brazier::StrToOperation(std::string operationName)
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

void Brazier::onToggle()
{
	this->interactSound->play();

	/*
	if (!this->saveKey.empty())
	{
		SaveManager::SoftSaveProfileData(this->saveKey, Value(this->isOn()));

		this->broadcastMapEvent(Brazier::MapEventTorchLogicSwitchSavePrefix + this->saveKey, ValueMap());
		this->broadcastMapEvent(Brazier::MapEventTorchLogicSwitchPrefix + this->colorName, ValueMap());
	}

	this->broadcastMapEvent(Brazier::MapEventCheckComplete, ValueMap());
	*/
}

void Brazier::onEnable()
{
	// this->burnSound->play(true);
	this->onSound->play();

	this->startFx();
}

void Brazier::onDisable()
{
	this->offSound->play();
	this->burnSound->stop();

	this->stopFx();
}

void Brazier::onOptimizationHide()
{
	this->stopFx();
}

void Brazier::onOptimizationShow()
{
	this->startFx();
}

void Brazier::startFx()
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

void Brazier::stopFx()
{
	this->glow->stopAllActions();
	this->fire->stopAnimation();
}

bool Brazier::isSolved()
{
	if (this->saveKey.empty())
	{
		return this->loadObjectStateOrDefault(Brazier::SaveKeyIsSolved, Value(false)).asBool();
	}
	else
	{
		return SaveManager::GetProfileDataOrDefault(this->saveKey + "_" + Brazier::SaveKeyIsSolved, Value(false)).asBool();
	}
}
