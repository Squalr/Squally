#include "InputsOutputs.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Localization/LocalizedLabel.h"
#include "Scenes/Cipher/Config.h"
#include "Scenes/Cipher/CipherState.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Inputs.h"
#include "Strings/Cipher/Outputs.h"

using namespace cocos2d;

InputsOutputs* InputsOutputs::create()
{
	InputsOutputs* instance = new InputsOutputs();

	instance->autorelease();

	return instance;
}

InputsOutputs::InputsOutputs()
{
	this->inputsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Cipher_Inputs::create());
	this->outputsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Cipher_Outputs::create());
	
	this->inputsLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);
	this->outputsLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);

	this->addChild(this->inputsLabel);
	this->addChild(this->outputsLabel);
}

InputsOutputs::~InputsOutputs()
{
}

void InputsOutputs::onEnter()
{
	super::onEnter();
}

void InputsOutputs::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->inputsLabel->setPosition(Vec2(visibleSize.width / 2.0f + Config::RightColumnCenter, visibleSize.height / 2.0f - 32.0f));
	this->outputsLabel->setPosition(Vec2(visibleSize.width / 2.0f + Config::RightColumnCenter, visibleSize.height / 2.0f - 32.0f));
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
