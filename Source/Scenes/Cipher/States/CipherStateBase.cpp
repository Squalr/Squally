#include "CipherStateBase.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

using namespace cocos2d;

CipherStateBase::CipherStateBase(CipherState::StateType stateType)
{
	this->stateType = stateType;
}

CipherStateBase::~CipherStateBase()
{
}

void CipherStateBase::initializeListeners()
{
	super::initializeListeners();

	EventListenerCustom* requestStateUpdateListener = EventListenerCustom::create(CipherState::RequestStateUpdateEvent, CC_CALLBACK_1(CipherStateBase::onRequestStateChangeEvent, this));
	EventListenerCustom* beforeStateUpdateListener = EventListenerCustom::create(CipherState::BeforeStateUpdateEvent, CC_CALLBACK_1(CipherStateBase::onBeforeStateChangeEvent, this));
	EventListenerCustom* onStateUpdateListener = EventListenerCustom::create(CipherState::OnStateUpdateEvent, CC_CALLBACK_1(CipherStateBase::onStateChangeEvent, this));

	this->addEventListener(requestStateUpdateListener);
	this->addEventListener(beforeStateUpdateListener);
	this->addEventListener(onStateUpdateListener);
}

void CipherStateBase::onRequestStateChangeEvent(EventCustom* eventCustom)
{
	CipherState* cipherState = (CipherState*)(eventCustom->getUserData());

	this->onAnyRequestStateChange(cipherState);
}

void CipherStateBase::onBeforeStateChangeEvent(EventCustom* eventCustom)
{
	CipherState* cipherState = (CipherState*)(eventCustom->getUserData());

	if (cipherState->stateType == this->stateType && cipherState->previousStateType != this->stateType)
	{
		this->onBeforeStateEnter(cipherState);
	}
	else if (cipherState->stateType != this->stateType && cipherState->previousStateType == this->stateType)
	{
		this->onStateExit(cipherState);
	}
}

void CipherStateBase::onStateChangeEvent(EventCustom* eventCustom)
{
	CipherState* cipherState = (CipherState*)(eventCustom->getUserData());

	if (cipherState->stateType == this->stateType)
	{
		if (cipherState->previousStateType == this->stateType)
		{
			this->onStateReload(cipherState);
		}
		else
		{
			this->onStateEnter(cipherState);
		}
	}

	this->onAnyStateChange(cipherState);
}

void CipherStateBase::onAnyStateChange(CipherState* cipherState)
{
}

void CipherStateBase::onAnyRequestStateChange(CipherState* cipherState)
{
}

void CipherStateBase::onBeforeStateEnter(CipherState* cipherState)
{
}

void CipherStateBase::onStateEnter(CipherState* cipherState)
{
}

void CipherStateBase::onStateReload(CipherState* cipherState)
{
}

void CipherStateBase::onStateExit(CipherState* cipherState)
{
}
