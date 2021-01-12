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

Brazier* Brazier::create(ValueMap& properties)
{
	Brazier* instance = new Brazier(properties);

	instance->autorelease();

	return instance;
}

Brazier::Brazier(ValueMap& properties) : super(properties, InteractType::None, Size(101.0f, 111.0f))
{
	this->torchColorName = GameUtils::getKeyOrDefault(this->properties, GameObject::PropertyColor, Value("")).asString();
	this->torch = Sprite::create(ObjectResources::Puzzles_Torch_Torch);
	this->fire = SmartAnimationSequenceNode::create();
	this->torchColor = Brazier::StrToColor(this->torchColorName);
	this->burnSound = WorldSound::create(SoundResources::Platformer_FX_Fire_FireSizzle1);
	this->onSound = WorldSound::create(SoundResources::Platformer_FX_Woosh_WooshFire2);
	this->offSound = WorldSound::create(SoundResources::Platformer_FX_Woosh_Woosh1);
	this->interactSound = WorldSound::create(SoundResources::Platformer_Objects_Machines_LampClick);

	this->onSound->setCustomMultiplier(0.25f);
	this->offSound->setCustomMultiplier(0.25f);

	switch (this->torchColor)
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

	this->addTag(this->operationName + "_" + this->torchColorName);

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
}

void Brazier::initializePositions()
{
	super::initializePositions();

	this->fire->setPosition(Vec2(0.0f, 16.0f));
	this->glow->setPosition(Vec2(0.0f, 0.0f));
}

Brazier::TorchColor Brazier::getTorchColor()
{
	return this->torchColor;
}

Brazier::TorchColor Brazier::StrToColor(std::string torchColorName)
{
	if (torchColorName == "blue")
	{
		return TorchColor::Blue;
	}
	else if (torchColorName == "green")
	{
		return TorchColor::Green;
	}
	else if (torchColorName == "purple")
	{
		return TorchColor::Purple;
	}
	else
	{
		return TorchColor::Red;
	}
}

void Brazier::onToggle()
{
	super::onToggle();
	
	this->interactSound->play();
}

void Brazier::onEnable(bool isInit)
{
	super::onEnable(isInit);

	// this->burnSound->play(true);
	
	if (!isInit)
	{
		this->onSound->play();
	}

	this->startFx();
}

void Brazier::onDisable(bool isInit)
{
	super::onDisable(isInit);

	if (!isInit)
	{
		this->offSound->play();
	}

	this->burnSound->stop();

	this->stopFx();
}

void Brazier::onOptimizationHide()
{
	super::onOptimizationHide();

	this->stopFx();
}

void Brazier::onOptimizationShow()
{
	super::onOptimizationShow();
	
	if (this->isOn())
	{
		this->startFx();
	}
}

void Brazier::startFx()
{
	switch (this->torchColor)
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
