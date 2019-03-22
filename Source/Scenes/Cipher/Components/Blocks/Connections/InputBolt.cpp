#include "InputBolt.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CipherEvents.h"
#include "Scenes/Cipher/Components/Blocks/Connections/Connection.h"
#include "Scenes/Cipher/Components/Blocks/Connections/OutputBolt.h"
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
	this->inputDebug = true;

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

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventRequestConnectionCreate, [=](EventCustom* eventCustom)
	{
		CipherEvents::CipherConnectionCreateArgs* args = static_cast<CipherEvents::CipherConnectionCreateArgs*>(eventCustom->getUserData());

		if (args != nullptr && !args->handled)
		{
			// Source bolt is output bolt
			if (dynamic_cast<OutputBolt*>(args->sourceBolt) != nullptr && GameUtils::intersects(this->connectButton, args->destination))
			{
				args->sourceBolt->setConnection(args->connection);
				args->connection->setInputBolt(this);

				args->handled = true;
			}
		}
	}));
}

void InputBolt::setConnection(Connection* connection)
{
	super::setConnection(connection);

	this->helperArrow->setVisible(this->connection == nullptr);
}

void InputBolt::hideHelp()
{
	this->helperArrow->setVisible(false);
}

void InputBolt::onConnectionStarted()
{
	if (this->connection != nullptr)
	{
		this->connection->setInputBolt(this, false);
		
		CipherEvents::TriggerConnectionStarted(CipherEvents::CipherConnectionStartedArgs(this->connection));
	}
}
