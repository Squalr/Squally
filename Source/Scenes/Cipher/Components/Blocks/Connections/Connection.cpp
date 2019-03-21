#include "Connection.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

Connection* Connection::create(InputBolt* source, OutputBolt* dest)
{
	Connection* instance = new Connection(source, dest);

	instance->autorelease();

	return instance;
}

Connection::Connection(InputBolt* source, OutputBolt* dest)
{
	this->connectionLine = Sprite::create(CipherResources::Connections_ConnectionSegment);
	this->connectionCap = Sprite::create(CipherResources::Connections_ConnectionSegmentCap);
	this->source = source;
	this->dest = dest;

	this->addChild(this->connectionLine);
	this->addChild(this->connectionCap);
}

Connection::~Connection()
{
}

void Connection::onEnter()
{
	super::onEnter();
}

void Connection::initializePositions()
{
	super::initializePositions();
}
