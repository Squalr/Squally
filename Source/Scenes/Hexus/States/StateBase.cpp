#include "StateBase.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

using namespace cocos2d;

StateBase::StateBase(GameState::StateType stateType)
{
	this->stateType = stateType;
}

StateBase::~StateBase()
{
}

void StateBase::initializeListeners()
{
	super::initializeListeners();

	EventListenerCustom* requestStateUpdateListener = EventListenerCustom::create(GameState::requestStateUpdateEvent, CC_CALLBACK_1(StateBase::onRequestStateChangeEvent, this));
	EventListenerCustom* beforeStateUpdateListener = EventListenerCustom::create(GameState::beforeStateUpdateEvent, CC_CALLBACK_1(StateBase::onBeforeStateChangeEvent, this));
	EventListenerCustom* onStateUpdateListener = EventListenerCustom::create(GameState::onStateUpdateEvent, CC_CALLBACK_1(StateBase::onStateChangeEvent, this));

	this->addEventListener(requestStateUpdateListener);
	this->addEventListener(beforeStateUpdateListener);
	this->addEventListener(onStateUpdateListener);
}

void StateBase::onRequestStateChangeEvent(EventCustom* eventCustom)
{
	GameState* gameState = (GameState*)(eventCustom->getUserData());

	this->onAnyRequestStateChange(gameState);
}

void StateBase::onBeforeStateChangeEvent(EventCustom* eventCustom)
{
	GameState* gameState = (GameState*)(eventCustom->getUserData());

	if (gameState->stateType == this->stateType && gameState->previousStateType != this->stateType)
	{
		this->onBeforeStateEnter(gameState);
	}
	else if (gameState->stateType != this->stateType && gameState->previousStateType == this->stateType)
	{
		this->onStateExit(gameState);
	}
}

void StateBase::onStateChangeEvent(EventCustom* eventCustom)
{
	GameState* gameState = (GameState*)(eventCustom->getUserData());

	if (gameState->stateType == this->stateType)
	{
		if (gameState->previousStateType == this->stateType)
		{
			this->onStateReload(gameState);
		}
		else
		{
			this->onStateEnter(gameState);
		}
	}

	this->onAnyStateChange(gameState);
}

void StateBase::onAnyStateChange(GameState* gameState)
{
}

void StateBase::onAnyRequestStateChange(GameState* gameState)
{
}

void StateBase::onBeforeStateEnter(GameState* gameState)
{
}

void StateBase::onStateEnter(GameState* gameState)
{
}

void StateBase::onStateReload(GameState* gameState)
{
}

void StateBase::onStateExit(GameState* gameState)
{
}
