#include "Bolt.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

Bolt* Bolt::create(bool isInput)
{
	Bolt* instance = new Bolt(isInput);

	instance->autorelease();

	return instance;
}

Bolt::Bolt(bool isInput)
{
	this->bolt = Sprite::create(CipherResources::Connections_ConnectionPlug);
	this->connectButton = ClickableNode::create(CipherResources::Connections_ConnectButton, CipherResources::Connections_ConnectButton);
	this->helperArrow = isInput ? Sprite::create(CipherResources::Connections_HelperArrowInput) : Sprite::create(CipherResources::Connections_HelperArrowOutput);
	this->isInput = isInput;

	bolt->setFlippedY(isInput);
	helperArrow->setFlippedY(isInput);

	this->connectButton->setVisible(false);

	this->addChild(this->bolt);
	this->addChild(this->connectButton);
	this->addChild(this->helperArrow);
}

Bolt::~Bolt()
{
}

void Bolt::onEnter()
{
	super::onEnter();
}

void Bolt::initializePositions()
{
	super::initializePositions();

	float offsetInit = this->isInput ? 20.0f : -20.0f;
	float offsetEnd = this->isInput ? 26.0f : -26.0f;

	this->connectButton->setPositionY(offsetInit);
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
