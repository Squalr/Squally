#include "BoltBase.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/InputEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CipherEvents.h"
#include "Scenes/Cipher/CipherConfig.h"
#include "Scenes/Cipher/CipherState.h"
#include "Scenes/Cipher/Components/Blocks/Connections/Connection.h"

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

	this->connectButton->setMouseDragCallback([=](InputEvents::MouseEventArgs* args)
	{
		if (!this->isCreatingConnection)
		{
			this->isCreatingConnection = true;

			this->setConnection(Connection::create());
			this->onConnectionUpdated();
		}

		if (this->isCreatingConnection && this->connection != nullptr)
		{
			this->connection->stretchToLocation(args->mouseCoords);
		}		
	});

	this->connectButton->setMouseReleaseNoHitTestCallback([=](InputEvents::MouseEventArgs* args)
	{
		if (this->isCreatingConnection && this->connection != nullptr)
		{
			this->isCreatingConnection = false;

			// Destroy the connection (it will be re-added to the OutputBolt if a destionation is found)
			this->setConnection(nullptr);

			CipherEvents::TriggerRequestConnectionCreate(CipherEvents::CipherConnectionCreateArgs(this, Connection::create(), args->mouseCoords));
		}
	});
}

void BoltBase::setConnection(Connection* connection)
{
	if (this->connection != nullptr)
	{
		this->removeChild(this->connection);
	}

	this->connection = connection;

	if (this->connection != nullptr)
	{
		this->addChild(this->connection);
	}
}

void BoltBase::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);

	switch(cipherState->stateType)
	{
		case CipherState::StateType::Neutral:
		{
			this->connectButton->enableInteraction();
			break;
		}
		default:
		{
			this->connectButton->disableInteraction();
			break;
		}
	}
}

void BoltBase::onConnectionUpdated()
{
}
