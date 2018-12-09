#include "SmartNode.h"

#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCEventListener.h"

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
