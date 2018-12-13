#include "SmartNode.h"

#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCEventListener.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/DeveloperMode/DeveloperModeController.h"
#include "Engine/Events/DeveloperModeEvents.h"
#include "Engine/Events/SceneEvents.h"

using namespace cocos2d;

SmartNode::SmartNode()
{
}

SmartNode::~SmartNode()
{
}

void SmartNode::onEnter()
{
	Node::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void SmartNode::onReenter()
{
	Node::onReenter();

	this->initializePositions();
	this->initializeListeners();
}

void SmartNode::initializePositions()
{
}

void SmartNode::initializeListeners()
{
	this->removeAllListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(DeveloperModeEvents::DeveloperModeModeEnableEvent, [=](EventCustom* args)
	{
		this->onDeveloperModeEnable();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(DeveloperModeEvents::DeveloperModeModeDisableEvent, [=](EventCustom* args)
	{
		this->onDeveloperModeDisable();
	}));
}

void SmartNode::onDeveloperModeEnable()
{
}

void SmartNode::onDeveloperModeDisable()
{
}

bool SmartNode::isDeveloperModeEnabled()
{
	return DeveloperModeController::getInstance()->isDeveloperModeEnabled();
}

void SmartNode::removeAllListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);
}

void SmartNode::addEventListener(EventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void SmartNode::addEventListenerIgnorePause(EventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	listener->setIgnorePause(true);

	this->addEventListener(listener);
}

void SmartNode::resume()
{
	Node::resume();

	this->initializeListeners();
}
