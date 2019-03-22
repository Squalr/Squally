#include "Connection.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

Connection* Connection::create()
{
	Connection* instance = new Connection();

	instance->autorelease();

	return instance;
}

Connection::Connection()
{
	this->connectionLine = Sprite::create(CipherResources::Connections_ConnectionSegment);
	this->connectionCap = Sprite::create(CipherResources::Connections_ConnectionSegmentCap);

	Texture2D::TexParams params = Texture2D::TexParams();
	params.minFilter = GL_LINEAR;
	params.magFilter = GL_LINEAR;
	params.wrapT = GL_REPEAT;
	params.wrapS = GL_REPEAT;
	this->connectionLine->getTexture()->setTexParameters(params);
	this->connectionLine->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->connectionCap->setFlippedY(true);

	this->addChild(this->connectionLine);
	this->addChild(this->connectionCap);
}

Connection::~Connection()
{
}

void Connection::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void Connection::initializePositions()
{
	super::initializePositions();
}

void Connection::initializeListeners()
{
	super::initializeListeners();
}

void Connection::update(float dt)
{
	super::update(dt);
}

void Connection::stretchToLocation(cocos2d::Vec2 location)
{
	const float MaxLength = 4096.0f;

	Vec2 thisPosition = GameUtils::getScreenBounds(this).origin;
	float distance = MathUtils::clamp(location.distance(thisPosition), 0.0f, MaxLength);
	float angleBetween = -std::atan2(thisPosition.y - location.y, thisPosition.x - location.x) - float(M_PI) / 2.0f;

	this->connectionLine->setTextureRect(Rect(0.0f, 0.0f, this->connectionLine->getContentSize().width, distance));
	this->connectionLine->setRotation(angleBetween * 180.0f / float(M_PI));
	this->connectionCap->setRotation(this->connectionLine->getRotation());
	this->connectionCap->setPosition(location - thisPosition);
}
