#include "InputBolt.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Events/CipherEvents.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

InputBolt* InputBolt::create()
{
	InputBolt* instance = new InputBolt();

	instance->autorelease();

	return instance;
}

InputBolt::InputBolt()
{
	this->bolt = Sprite::create(CipherResources::Connections_ConnectionPlug);
	this->helperArrow = Sprite::create(CipherResources::Connections_HelperArrowInput);

	bolt->setFlippedY(true);
	helperArrow->setFlippedY(true);

	this->addChild(this->bolt);
	this->addChild(this->helperArrow);
}

InputBolt::~InputBolt()
{
}

void InputBolt::onEnter()
{
	super::onEnter();
}

void InputBolt::initializePositions()
{
	super::initializePositions();

	const float offsetInit = 20.0f;
	const float offsetEnd = 26.0f;

	this->helperArrow->setPositionY(offsetInit);
	
	this->helperArrow->runAction(
		RepeatForever::create(
			Sequence::create(
				MoveTo::create(1.25f, Vec2(0.0f, offsetInit)),
				MoveTo::create(1.25f, Vec2(0.0f, offsetEnd)),
				nullptr
			)
		)
	);
}

void InputBolt::initializeListeners()
{
	super::initializeListeners();
}
