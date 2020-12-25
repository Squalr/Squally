#include "OutputBolt.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CipherEvents.h"
#include "Scenes/Cipher/CipherConfig.h"
#include "Scenes/Cipher/Components/Blocks/Connections/Connection.h"
#include "Scenes/Cipher/Components/Blocks/Connections/InputBolt.h"

#include "Resources/CipherResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

OutputBolt* OutputBolt::create()
{
	OutputBolt* instance = new OutputBolt();

	instance->autorelease();

	return instance;
}

OutputBolt::OutputBolt()
{
	this->bolt = Sprite::create(CipherResources::Connections_ConnectionPlug);
	this->helperArrow = Sprite::create(CipherResources::Connections_HelperArrowOutput);

	this->addChild(this->bolt);
	this->addChild(this->helperArrow);
}

OutputBolt::~OutputBolt()
{
}

void OutputBolt::onEnter()
{
	super::onEnter();
}

void OutputBolt::initializePositions()
{
	super::initializePositions();

	const float offsetInit = -20.0f;
	const float offsetEnd = -26.0f;

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

void OutputBolt::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventConnectionUpdated, [=](EventCustom* eventCustom)
	{
		CipherEvents::CipherConnectionUpdatedArgs* args = static_cast<CipherEvents::CipherConnectionUpdatedArgs*>(eventCustom->getData());

		// Enforce that every input only has one output flowing into it
		if (args != nullptr && this->connection != nullptr && args->connection != this->connection)
		{
			if (args->connection->getInputBolt() == this->connection->getInputBolt())
			{
				this->setConnection(nullptr);
			}
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventRequestConnectionCreate, [=](EventCustom* eventCustom)
	{
		CipherEvents::CipherConnectionCreateArgs* args = static_cast<CipherEvents::CipherConnectionCreateArgs*>(eventCustom->getData());

		if (args != nullptr && !args->isHandled())
		{
			// Source bolt is input bolt
			if (dynamic_cast<InputBolt*>(args->sourceBolt) != nullptr && GameUtils::intersects(this->connectButton, args->destination, false))
			{
				this->setConnection(args->connection);
				this->connection->setInputBolt(dynamic_cast<InputBolt*>(args->sourceBolt));
				CipherEvents::TriggerConnectionUpdated(CipherEvents::CipherConnectionUpdatedArgs(this->connection));

				args->handle();
			}
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventConnectionDestroy, [=](EventCustom* eventCustom)
	{
		CipherEvents::CipherConnectionDestroyArgs* args = static_cast<CipherEvents::CipherConnectionDestroyArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			if (this->connection != nullptr && this->connection->getInputBolt() == args->inputBolt)
			{
				this->setConnection(nullptr);
			}
		}
	}));
}

void OutputBolt::execute(char value, std::function<void()> onExecuteComplete)
{
	if (this->connection != nullptr)
	{
		this->connection->execute(value, onExecuteComplete);
	}
	else
	{
		onExecuteComplete();
	}
}

void OutputBolt::setConnection(Connection* connection)
{
	super::setConnection(connection);

	this->helperArrow->setVisible(this->connection == nullptr);
}
