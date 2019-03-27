#include "BoltBase.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/MouseEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CipherEvents.h"
#include "Scenes/Cipher/Components/Blocks/Connections/Connection.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

BoltBase::BoltBase()
{
	this->connectButton = ClickableNode::create(UIResources::EmptyImage, UIResources::EmptyImage);
	this->isCreatingConnection = false;
	this->connection = nullptr;
	this->inputDebug = false;

	this->connectButton->setContentSize(Size(48.0f, 48.0f));

	this->addChild(this->connectButton);
}

BoltBase::~BoltBase()
{
}

void BoltBase::onEnter()
{
	super::onEnter();
}

void BoltBase::initializePositions()
{
	super::initializePositions();
}

void BoltBase::initializeListeners()
{
	super::initializeListeners();

	this->connectButton->setMouseDragCallback([=](MouseEvents::MouseEventArgs* args)
	{
		if (!this->isCreatingConnection)
		{
			this->setConnection(nullptr);

			this->isCreatingConnection = true;

			this->setConnection(Connection::create());
			this->onConnectionUpdated();
		}

		if (this->isCreatingConnection && this->connection != nullptr)
		{
			this->connection->stretchToLocation(args->mouseCoords);
		}		
	});

	this->addEventListener(EventListenerCustom::create(MouseEvents::EventMouseMove, ([=](EventCustom* eventCustom)
	{
		if (this->connection != nullptr)
		{
			MouseEvents::MouseEventArgs* args = static_cast<MouseEvents::MouseEventArgs*>(eventCustom->getUserData());

			if (args != nullptr)
			{
				this->connection->stretchToLocation(args->mouseCoords);
			}
		}
	})));

	this->connectButton->setMouseReleaseNoHitTestCallback([=](MouseEvents::MouseEventArgs* args)
	{
		if (this->isCreatingConnection && this->connection != nullptr)
		{
			this->isCreatingConnection = false;

			// Release the connection (it will be re-added to the OutputBolt if a destionation is found)
			Connection* connection = this->connection;
			this->setConnection(nullptr);

			CipherEvents::TriggerRequestConnectionCreate(CipherEvents::CipherConnectionCreateArgs(this, connection, args->mouseCoords));
		}
	});
}

void BoltBase::setConnection(Connection* connection)
{
	if (this->connection != nullptr)
	{
		GameUtils::changeParent(this->connection, nullptr, false);
	}

	this->connection = connection;

	if (this->connection != nullptr)
	{
		this->addChild(this->connection);
	}
}

void BoltBase::onConnectionUpdated()
{
}
