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

	EventListenerCustom* requestStateChangeListener = EventListenerCustom::create(CipherState::requestStateUpdateEvent, CC_CALLBACK_1(CipherComponentBase::onRequestStateChangeEvent, this));
	EventListenerCustom* beforeStateChangeListener = EventListenerCustom::create(CipherState::beforeStateUpdateEvent, CC_CALLBACK_1(CipherComponentBase::onBeforeStateChangeEvent, this));
	EventListenerCustom* stateChangeListener = EventListenerCustom::create(CipherState::onStateUpdateEvent, CC_CALLBACK_1(CipherComponentBase::onStateChangeEvent, this));

	this->addEventListener(requestStateChangeListener);
	this->addEventListener(beforeStateChangeListener);
	this->addEventListener(stateChangeListener);
}

void CipherComponentBase::onRequestStateChangeEvent(EventCustom* eventCustom)
{
	this->onAnyRequestStateChange((CipherState*)(eventCustom->getUserData()));
}

void CipherComponentBase::onBeforeStateChangeEvent(EventCustom* eventCustom)
{
	this->onBeforeStateChange((CipherState*)(eventCustom->getUserData()));
}

void CipherComponentBase::onStateChangeEvent(EventCustom* eventCustom)
{
	this->onAnyStateChange((CipherState*)(eventCustom->getUserData()));
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
