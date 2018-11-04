#include "ComponentBase.h"

ComponentBase::ComponentBase()
{
}

ComponentBase::~ComponentBase()
{
}

void ComponentBase::initializeListeners()
{
	SmartNode::initializeListeners();

	EventListenerCustom* beforeStateChangeListener = EventListenerCustom::create(GameState::beforeStateUpdateEvent, CC_CALLBACK_1(ComponentBase::onBeforeStateChangeEvent, this));
	EventListenerCustom* stateChangeListener = EventListenerCustom::create(GameState::onStateUpdateEvent, CC_CALLBACK_1(ComponentBase::onStateChangeEvent, this));

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(beforeStateChangeListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(stateChangeListener, this);
}

void ComponentBase::onBeforeStateChangeEvent(EventCustom* eventCustom)
{
	this->onBeforeStateChange((GameState*)(eventCustom->getUserData()));
}

void ComponentBase::onStateChangeEvent(EventCustom* eventCustom)
{
	this->onAnyStateChange((GameState*)(eventCustom->getUserData()));
}

void ComponentBase::onBeforeStateChange(GameState* gameState)
{
}

void ComponentBase::onAnyStateChange(GameState* gameState)
{
}