#include "InputsOutputs.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Scenes/Cipher/Config.h"
#include "Scenes/Cipher/CipherState.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

InputsOutputs* InputsOutputs::create()
{
	InputsOutputs* instance = new InputsOutputs();

	instance->autorelease();

	return instance;
}

InputsOutputs::InputsOutputs()
{
	this->playerSocketA = Sprite::create(CipherResources::AsciiButton);
	this->playerSocketB = Sprite::create(CipherResources::AsciiButton);
	this->playerSkullA = Sprite::create(CipherResources::AsciiButton);
	this->playerSkullB = Sprite::create(CipherResources::AsciiButton);
	this->enemySocketA = Sprite::create(CipherResources::AsciiButton);
	this->enemySocketB = Sprite::create(CipherResources::AsciiButton);
	this->enemySkullA = Sprite::create(CipherResources::AsciiButton);
	this->enemySkullB = Sprite::create(CipherResources::AsciiButton);

	this->addChild(this->playerSocketA);
	this->addChild(this->playerSocketB);
	this->addChild(this->playerSkullA);
	this->addChild(this->playerSkullB);
	this->addChild(this->enemySocketA);
	this->addChild(this->enemySocketB);
	this->addChild(this->enemySkullA);
	this->addChild(this->enemySkullB);
}

InputsOutputs::~InputsOutputs()
{
}

void InputsOutputs::onEnter()
{
	super::onEnter();

	this->playerSkullA->setOpacity(0);
	this->playerSkullB->setOpacity(0);
	this->enemySkullA->setOpacity(0);
	this->enemySkullB->setOpacity(0);
}

void InputsOutputs::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void InputsOutputs::onBeforeStateChange(CipherState* cipherState)
{
	super::onBeforeStateChange(cipherState);
}

void InputsOutputs::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);

	this->updateDisplayedLosses(cipherState);
}

void InputsOutputs::updateDisplayedLosses(CipherState* cipherState)
{
}
