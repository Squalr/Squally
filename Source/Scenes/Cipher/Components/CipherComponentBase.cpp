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

	this->addEventListener(EventListenerCustom::create(CipherEvents::EventBeforeRequestStateUpdate, [=](EventCustom* eventCustom)
	{
		this->onBeforeAnyRequestStateChange((CipherState*)(eventCustom->getUserData()));
	}));
	this->addEventListener(EventListenerCustom::create(CipherEvents::EventRequestStateUpdate, [=](EventCustom* eventCustom)
	{
		this->onAnyRequestStateChange((CipherState*)(eventCustom->getUserData()));
	}));
	this->addEventListener(EventListenerCustom::create(CipherEvents::EventBeforeStateUpdate, [=](EventCustom* eventCustom)
	{
		this->onBeforeStateChange((CipherState*)(eventCustom->getUserData()));
	}));
	this->addEventListener(EventListenerCustom::create(CipherEvents::EventOnStateUpdate, [=](EventCustom* eventCustom)
	{
		this->onAnyStateChange((CipherState*)(eventCustom->getUserData()));
	}));
}

void CipherComponentBase::onBeforeStateChange(CipherState* gameState)
{
}

void CipherComponentBase::onBeforeAnyRequestStateChange(CipherState* gameState)
{
}

void CipherComponentBase::onAnyRequestStateChange(CipherState* gameState)
{
}

void CipherComponentBase::onAnyStateChange(CipherState* gameState)
{
}
