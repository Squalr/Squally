#include "CipherStateStartGame.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

using namespace cocos2d;

CipherStateStartGame* CipherStateStartGame::create()
{
	CipherStateStartGame* instance = new CipherStateStartGame();

	instance->autorelease();

	return instance;
}

CipherStateStartGame::CipherStateStartGame() : super(CipherState::StateType::GameStart)
{
}

CipherStateStartGame::~CipherStateStartGame()
{
}

void CipherStateStartGame::onBeforeStateEnter(CipherState* cipherState)
{
	super::onBeforeStateEnter(cipherState);

	// Clear all state variables before game start
	cipherState->blockContent->removeAllChildren();
	cipherState->connectionContent->removeAllChildren();
	cipherState->inputOutputMap.clear();
	cipherState->userBlocks.clear();
}

void CipherStateStartGame::onStateEnter(CipherState* cipherState)
{
	super::onStateEnter(cipherState);

	CipherState::updateState(cipherState, CipherState::StateType::LoadInitialState);
}

void CipherStateStartGame::onStateReload(CipherState* cipherState)
{
	super::onStateReload(cipherState);
}

void CipherStateStartGame::onStateExit(CipherState* cipherState)
{
	super::onStateExit(cipherState);
}
