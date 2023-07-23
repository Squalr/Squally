#include "Switch.h"

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

const std::string Switch::MapKey = "switch";

Switch* Switch::create(ValueMap& properties)
{
	Switch* instance = new Switch(properties);

	instance->autorelease();

	return instance;
}

Switch::Switch(ValueMap& properties) : super(properties, InteractType::Input, CSize(35.0f, 56.0f))
{
	this->switchOn = Sprite::create(ObjectResources::Switches_Switch_SwitchOn);
	this->switchOff = Sprite::create(ObjectResources::Switches_Switch_SwitchOff);
	this->interactSound = WorldSound::create(SoundResources::Platformer_Objects_Machines_LampClick);

	this->frontNode->addChild(this->switchOn);
	this->frontNode->addChild(this->switchOff);
	this->addChild(this->interactSound);
}

Switch::~Switch()
{
}

void Switch::onEnter()
{
	super::onEnter();
}

void Switch::initializePositions()
{
	super::initializePositions();
}

void Switch::onToggle(bool isInstant)
{
	super::onToggle(isInstant);
	
	this->interactSound->play();
	this->broadcastMapEvent(this->getSendEvent(), ValueMap());
}

void Switch::onEnable(bool isInit, bool isInstant)
{
	super::onEnable(isInit, isInstant);

	this->switchOn->setVisible(true);
	this->switchOff->setVisible(false);
}

void Switch::onDisable(bool isInit, bool isInstant)
{
	super::onDisable(isInit, isInstant);

	this->switchOn->setVisible(false);
	this->switchOff->setVisible(true);
}
