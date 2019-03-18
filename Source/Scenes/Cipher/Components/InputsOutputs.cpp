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
