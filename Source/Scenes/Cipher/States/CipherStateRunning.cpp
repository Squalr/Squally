#include "CipherStateRunning.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

using namespace cocos2d;

CipherStateRunning* CipherStateRunning::create()
{
	CipherStateRunning* instance = new CipherStateRunning();

	instance->autorelease();

	return instance;
}

CipherStateRunning::CipherStateRunning() : super(CipherState::StateType::Running)
{
}

CipherStateRunning::~CipherStateRunning()
{
}

void CipherStateRunning::onBeforeStateEnter(CipherState* cipherState)
{
	super::onBeforeStateEnter(cipherState);
}

void CipherStateRunning::onStateEnter(CipherState* cipherState)
{
	super::onStateEnter(cipherState);

	this->runAction(Sequence::create(
		DelayTime::create(0.5f),
		CallFunc::create([=]()
		{
			CipherState::updateState(cipherState, CipherState::StateType::Neutral);
		}),
		nullptr
	));
}

void CipherStateRunning::onStateReload(CipherState* cipherState)
{
	super::onStateReload(cipherState);
}

void CipherStateRunning::onStateExit(CipherState* cipherState)
{
	super::onStateExit(cipherState);
}
