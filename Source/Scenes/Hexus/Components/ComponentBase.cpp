#include "ComponentBase.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Scenes/Hexus/GameState.h"

using namespace cocos2d;

ComponentBase::ComponentBase()
{
}

ComponentBase::~ComponentBase()
{
}

void ComponentBase::initializeListeners()
{
	super::initializeListeners();

	EventListenerCustom* requestStateChangeListener = EventListenerCustom::create(GameState::requestStateUpdateEvent, CC_CALLBACK_1(ComponentBase::onRequestStateChangeEvent, this));
	EventListenerCustom* beforeStateChangeListener = EventListenerCustom::create(GameState::beforeStateUpdateEvent, CC_CALLBACK_1(ComponentBase::onBeforeStateChangeEvent, this));
	EventListenerCustom* stateChangeListener = EventListenerCustom::create(GameState::onStateUpdateEvent, CC_CALLBACK_1(ComponentBase::onStateChangeEvent, this));

	this->addEventListener(requestStateChangeListener);
	this->addEventListener(beforeStateChangeListener);
	this->addEventListener(stateChangeListener);
}

void ComponentBase::onRequestStateChangeEvent(EventCustom* eventCustom)
{
	this->onAnyRequestStateChange((GameState*)(eventCustom->getUserData()));
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

void ComponentBase::onAnyRequestStateChange(GameState* gameState)
{
}

void ComponentBase::onAnyStateChange(GameState* gameState)
{
}
