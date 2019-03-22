#include "CipherStateLoadInitialState.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"

using namespace cocos2d;

CipherStateLoadInitialState* CipherStateLoadInitialState::create()
{
	CipherStateLoadInitialState* instance = new CipherStateLoadInitialState();

	instance->autorelease();

	return instance;
}

CipherStateLoadInitialState::CipherStateLoadInitialState() : super(CipherState::StateType::LoadInitialState)
{
}

CipherStateLoadInitialState::~CipherStateLoadInitialState()
{
}

void CipherStateLoadInitialState::onBeforeStateEnter(CipherState* cipherState)
{
	super::onBeforeStateEnter(cipherState);

	// Load initial state variables
	if (cipherState->puzzleData != nullptr)
	{
		cipherState->inputOutputMap = cipherState->puzzleData->getInputOutputMap();
	}
	
	cipherState->loadCipherAtIndex(0);
}

void CipherStateLoadInitialState::onStateEnter(CipherState* cipherState)
{
	super::onStateEnter(cipherState);

	this->runAction(Sequence::create(
		DelayTime::create(0.1f),
		CallFunc::create([=]()
		{
			CipherState::updateState(cipherState, CipherState::StateType::Neutral);
		}),
		nullptr
	));
}

void CipherStateLoadInitialState::onStateReload(CipherState* cipherState)
{
	super::onStateReload(cipherState);
}

void CipherStateLoadInitialState::onStateExit(CipherState* cipherState)
{
	super::onStateExit(cipherState);
}
