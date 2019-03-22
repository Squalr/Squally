#include "CipherStateNeutral.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

using namespace cocos2d;

CipherStateNeutral* CipherStateNeutral::create()
{
	CipherStateNeutral* instance = new CipherStateNeutral();

	instance->autorelease();

	return instance;
}

CipherStateNeutral::CipherStateNeutral() : super(CipherState::StateType::Neutral)
{
}

CipherStateNeutral::~CipherStateNeutral()
{
}

void CipherStateNeutral::onBeforeStateEnter(CipherState* cipherState)
{
	super::onBeforeStateEnter(cipherState);
}

void CipherStateNeutral::onStateEnter(CipherState* cipherState)
{
	super::onStateEnter(cipherState);
}

void CipherStateNeutral::onStateReload(CipherState* cipherState)
{
	super::onStateReload(cipherState);
}

void CipherStateNeutral::onStateExit(CipherState* cipherState)
{
	super::onStateExit(cipherState);
}
