#include "CipherStateVictory.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

using namespace cocos2d;

CipherStateVictory* CipherStateVictory::create()
{
	CipherStateVictory* instance = new CipherStateVictory();

	instance->autorelease();

	return instance;
}

CipherStateVictory::CipherStateVictory() : super(CipherState::StateType::Victory)
{
}

CipherStateVictory::~CipherStateVictory()
{
}

void CipherStateVictory::onBeforeStateEnter(CipherState* cipherState)
{
	super::onBeforeStateEnter(cipherState);
}

void CipherStateVictory::onStateEnter(CipherState* cipherState)
{
	super::onStateEnter(cipherState);

	this->runAction(Sequence::create(
		DelayTime::create(0.5f),
		CallFunc::create([=]()
		{
			CipherState::updateState(cipherState, CipherState::StateType::GameEnd);
		}),
		nullptr
	));
}

void CipherStateVictory::onStateReload(CipherState* cipherState)
{
	super::onStateReload(cipherState);
}

void CipherStateVictory::onStateExit(CipherState* cipherState)
{
	super::onStateExit(cipherState);
}
