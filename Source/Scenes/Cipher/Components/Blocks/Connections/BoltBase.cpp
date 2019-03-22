#include "BoltBase.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/MouseEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Events/CipherEvents.h"
#include "Scenes/Cipher/Components/Blocks/Connections/Connection.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

BoltBase::BoltBase()
{
	this->connectButton = ClickableNode::create(UIResources::EmptyImage, UIResources::EmptyImage);
	this->isCreatingConnection = false;
	this->isInClickCreateMode = false;
	this->connection = nullptr;

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

	// Method 1: Click source, click destination
	this->connectButton->setClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		if (this->connection == nullptr)
		{
			this->connection = Connection::create();
			this->isCreatingConnection = true;
			this->isInClickCreateMode = true;

			this->addChild(this->connection);
		}
	});

	// Method 2: Drag from source to destination
	this->connectButton->setMouseDragCallback([=](MouseEvents::MouseEventArgs* args)
	{
		if (this->connection == nullptr)
		{
			this->connection = Connection::create();
			this->isCreatingConnection = true;
			
			this->addChild(this->connection);
		}
		else
		{
			if (this->isCreatingConnection && this->connection != nullptr)
			{
				if (args != nullptr)
				{
					this->connection->stretchToLocation(args->mouseCoords);
				}
			}
		}
		
	});

	this->addEventListener(EventListenerCustom::create(MouseEvents::EventMouseMove, ([=](EventCustom* eventCustom)
	{
		if (this->isInClickCreateMode && this->connection != nullptr)
		{
			MouseEvents::MouseEventArgs* args = static_cast<MouseEvents::MouseEventArgs*>(eventCustom->getUserData());

			if (args != nullptr)
			{
				this->connection->stretchToLocation(args->mouseCoords);
			}
		}
	})));

	this->connectButton->setMouseReleaseCallback([=](MouseEvents::MouseEventArgs*)
	{

	});
}
