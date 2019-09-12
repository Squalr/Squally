#include "CipherStateBase.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Events/CipherEvents.h"

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

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventRequestStateUpdate, [=](EventCustom* eventCustom)
	{
		CipherState* cipherState = (CipherState*)(eventCustom->getUserData());

		if (cipherState != nullptr)
		{
			this->onAnyRequestStateChange(cipherState);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventBeforeStateUpdate, [=](EventCustom* eventCustom)
	{
		CipherState* cipherState = (CipherState*)(eventCustom->getUserData());

		if (cipherState != nullptr)
		{
			if (cipherState->stateType == this->stateType && cipherState->previousStateType != this->stateType)
			{
				this->onBeforeStateEnter(cipherState);
			}
			else if (cipherState->stateType != this->stateType && cipherState->previousStateType == this->stateType)
			{
				this->onStateExit(cipherState);
			}
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventOnStateUpdate, [=](EventCustom* eventCustom)
	{
		CipherState* cipherState = (CipherState*)(eventCustom->getUserData());

		if (cipherState != nullptr)
		{
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
	}));
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
