#include "Connection.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Scenes/Cipher/Components/Blocks/Connections/InputBolt.h"
#include "Scenes/Cipher/Config.h"
#include "Scenes/Platformer/WorldMap/FX/Lightning.h"

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
	this->lightningEffect = Lightning::create();
	this->inputBolt = nullptr;
	this->trackBolt = false;
	this->currentStretchPosition = Vec2::ZERO;
	this->lightningProgress = 0;

	Texture2D::TexParams params = Texture2D::TexParams();
	params.minFilter = GL_LINEAR;
	params.magFilter = GL_LINEAR;
	params.wrapT = GL_REPEAT;
	params.wrapS = GL_REPEAT;
	this->connectionLine->getTexture()->setTexParameters(params);
	this->connectionLine->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->connectionCap->setFlippedY(true);
	this->lightningEffect->setVisible(false);

	this->lightningEffect->setManualDelay(0.0f);
	this->lightningEffect->setScale(0.35f);

	this->addChild(this->connectionLine);
	this->addChild(this->connectionCap);
	this->addChild(this->lightningEffect);
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
	this->lightningEffect->setRotation(this->connectionLine->getRotation());

	this->currentStretchPosition = location;
}

InputBolt* Connection::getInputBolt()
{
	return this->inputBolt;
}

void Connection::runElectricityEffect(std::function<void()> onEffectComplete)
{
	Vec2 thisPosition = GameUtils::getScreenBounds(this).origin;
	this->lightningEffect->setVisible(true);
	this->lightningProgress = 0;

	this->lightningEffect->setLightningCallback([=]
	{
		switch(this->lightningProgress++)
		{
			case 0:
			{
				this->lightningEffect->setPosition(Vec2::ZERO);
				break;
			}
			case 1:
			{
				this->lightningEffect->setPosition((this->currentStretchPosition - thisPosition) / 2.0f);
				break;
			}
			case 2:
			{
				this->lightningEffect->setPosition(this->currentStretchPosition - thisPosition);
				break;
			}
			case 3:
			{
				onEffectComplete();
				this->lightningEffect->setVisible(false);
				break;
			}
			default:
			{
				this->lightningEffect->setVisible(false);
				break;
			}
		}
	});

}
