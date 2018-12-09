#include "SmartScene.h"

#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCEventListener.h"

using namespace cocos2d;

SmartScene::SmartScene()
{
}

SmartScene::~SmartScene()
{
}

void SmartScene::onEnter()
{
	Scene::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void SmartScene::initializePositions()
{
}

void SmartScene::initializeListeners()
{
	this->removeAllListeners();
}

void SmartScene::removeAllListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);
}

void SmartScene::addEventListener(EventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void SmartScene::addEventListenerIgnorePause(EventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	listener->setIgnorePause(true);

	this->addEventListener(listener);
}

void SmartScene::resume()
{
	Scene::resume();

	this->initializeListeners();
}
