#include "SmartScene.h"

SmartScene::SmartScene()
{
}

SmartScene::~SmartScene()
{
}

void SmartScene::onEnter()
{
	Node::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void SmartScene::initializePositions()
{

}

void SmartScene::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);
}
