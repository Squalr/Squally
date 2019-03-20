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

	bolt->setFlippedY(isInput);

	this->addChild(this->bolt);
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
}
