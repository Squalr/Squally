#include "ComponentBase.h"

ComponentBase::ComponentBase()
{
}

ComponentBase::~ComponentBase()
{
}

void ComponentBase::onEnter()
{
	Node::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void ComponentBase::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void ComponentBase::initializeListeners()
{
	EventListenerCustom* stateListener = EventListenerCustom::create(GameState::onStateUpdateEvent, CC_CALLBACK_1(ComponentBase::onStateChangeEvent, this));

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(stateListener, this);
}

void ComponentBase::onStateChangeEvent(EventCustom* eventCustom)
{
	this->onStateChange((GameState*)(eventCustom->getUserData()));
}

void ComponentBase::onStateChange(GameState* gameState)
{
}