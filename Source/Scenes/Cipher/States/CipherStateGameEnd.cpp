#include "CipherStateGameEnd.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

using namespace cocos2d;

CipherStateGameEnd* CipherStateGameEnd::create()
{
	CipherStateGameEnd* instance = new CipherStateGameEnd();

	instance->autorelease();

	return instance;
}

CipherStateGameEnd::CipherStateGameEnd() : super(CipherState::StateType::GameEnd)
{
}

CipherStateGameEnd::~CipherStateGameEnd()
{
}

void CipherStateGameEnd::onBeforeStateEnter(CipherState* cipherState)
{
	super::onBeforeStateEnter(cipherState);
}

void CipherStateGameEnd::onStateEnter(CipherState* cipherState)
{
	super::onStateEnter(cipherState);
}

void CipherStateGameEnd::onStateReload(CipherState* cipherState)
{
	super::onStateReload(cipherState);
}

void CipherStateGameEnd::onStateExit(CipherState* cipherState)
{
	super::onStateExit(cipherState);
}
