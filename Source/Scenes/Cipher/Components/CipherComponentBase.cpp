#include "CipherComponentBase.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Scenes/Cipher/CipherState.h"

using namespace cocos2d;

CipherComponentBase::CipherComponentBase()
{
}

CipherComponentBase::~CipherComponentBase()
{
}

void CipherComponentBase::initializeListeners()
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
			if (cipherState->stateType == cipherState->stateType && cipherState->previousStateType != cipherState->stateType)
			{
				this->onBeforeStateEnter(cipherState);
			}
			else if (cipherState->stateType != cipherState->stateType && cipherState->previousStateType == cipherState->stateType)
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
			if (cipherState->stateType == cipherState->stateType)
			{
				if (cipherState->previousStateType == cipherState->stateType)
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

void CipherComponentBase::onAnyStateChange(CipherState* cipherState)
{
}

void CipherComponentBase::onAnyRequestStateChange(CipherState* cipherState)
{
}

void CipherComponentBase::onBeforeStateEnter(CipherState* cipherState)
{
}

void CipherComponentBase::onStateEnter(CipherState* cipherState)
{
}

void CipherComponentBase::onStateReload(CipherState* cipherState)
{
}

void CipherComponentBase::onStateExit(CipherState* cipherState)
{
}
