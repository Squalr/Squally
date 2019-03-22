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
}

void CipherStateLoadInitialState::onStateEnter(CipherState* cipherState)
{
	super::onStateEnter(cipherState);

	cipherState->inputOutputMap = cipherState->puzzleData->getInputOutputMap();

	CipherState::updateState(cipherState, CipherState::StateType::LoadInitialState);
}

void CipherStateLoadInitialState::onStateReload(CipherState* cipherState)
{
	super::onStateReload(cipherState);
}

void CipherStateLoadInitialState::onStateExit(CipherState* cipherState)
{
	super::onStateExit(cipherState);
}
