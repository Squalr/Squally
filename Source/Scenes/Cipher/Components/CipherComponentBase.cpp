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
			this->onBeforeStateChange(cipherState);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventOnStateUpdate, [=](EventCustom* eventCustom)
	{
		CipherState* cipherState = (CipherState*)(eventCustom->getUserData());

		if (cipherState != nullptr)
		{
			this->onAnyStateChange(cipherState);
		}
	}));
}

void CipherComponentBase::onBeforeStateChange(CipherState* cipherState)
{
}

void CipherComponentBase::onAnyRequestStateChange(CipherState* cipherState)
{
}

void CipherComponentBase::onAnyStateChange(CipherState* cipherState)
{
}
