#include "Connection.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Scenes/Cipher/Components/Blocks/Connections/InputBolt.h"
#include "Scenes/Cipher/Components/Blocks/Connections/Lightning.h"
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
	this->connectionPulse = Sprite::create(CipherResources::Connections_ConnectionPulse);
	this->lightningEffectSource = Lightning::create();
	this->lightningEffectDest = Lightning::create();
	this->inputBolt = nullptr;
	this->trackBolt = false;
	this->currentStretchPosition = Vec2::ZERO;

	Texture2D::TexParams params = Texture2D::TexParams();
	params.minFilter = GL_LINEAR;
	params.magFilter = GL_LINEAR;
	params.wrapT = GL_REPEAT;
	params.wrapS = GL_REPEAT;
	this->connectionLine->getTexture()->setTexParameters(params);
	this->connectionLine->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->connectionCap->setFlippedY(true);

	this->lightningEffectSource->setManualDelay(0.0f);
	this->lightningEffectDest->setManualDelay(0.0f);
	this->lightningEffectSource->setScale(0.35f);
	this->lightningEffectDest->setScale(0.35f);

	this->addChild(this->connectionLine);
	this->addChild(this->connectionCap);
	this->addChild(this->connectionPulse);
	this->addChild(this->lightningEffectSource);
	this->addChild(this->lightningEffectDest);
}

Connection::~Connection()
{
}

void Connection::onEnter()
{
	super::onEnter();

	this->connectionPulse->setVisible(false);

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

	if (this->inputBolt != nullptr && this->trackBolt)
	{
		this->stretchToLocation(GameUtils::getScreenBounds(this->inputBolt).origin);
	}
}

void Connection::execute(char value, std::function<void()> onExecuteComplete)
{
	if (this->inputBolt != nullptr)
	{
		this->runElectricityEffect([=]()
		{
			this->inputBolt->execute(value, onExecuteComplete);
		});
	}
	else
	{
		onExecuteComplete();
	}
}

void Connection::setInputBolt(InputBolt* inputBolt, bool trackBolt)
{
	this->inputBolt = inputBolt;
	this->trackBolt = trackBolt;
	
	if (this->inputBolt != nullptr)
	{
		this->inputBolt->hideHelp();
	}
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

	this->currentStretchPosition = location;
}

InputBolt* Connection::getInputBolt()
{
	return this->inputBolt;
}

void Connection::runElectricityEffect(std::function<void()> onEffectComplete)
{
	Vec2 thisPosition = GameUtils::getScreenBounds(this).origin;

	this->connectionPulse->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			this->lightningEffectSource->setPosition(Vec2::ZERO);
			this->lightningEffectDest->setPosition(this->currentStretchPosition - thisPosition);
			this->connectionPulse->setPosition(Vec2::ZERO);
			this->connectionPulse->setVisible(true);
			this->lightningEffectSource->playAnimations(false);
		}),
		MoveTo::create(0.25f, this->currentStretchPosition - thisPosition),
		CallFunc::create([=]()
		{
			this->connectionPulse->setVisible(false);
			this->lightningEffectDest->playAnimations(false);
			onEffectComplete();
		}),
		nullptr
	));
}
