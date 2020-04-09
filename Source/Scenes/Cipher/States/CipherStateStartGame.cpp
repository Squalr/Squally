#include "CipherStateStartGame.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Scenes/Cipher/Components/Blocks/Special/DestinationBlock.h"
#include "Scenes/Cipher/Components/Blocks/Special/SourceBlock.h"

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
	cipherState->userConnections.clear();

	for (auto next : cipherState->inputBlocks)
	{
		next->removeConnections();
	}

	for (auto next : cipherState->outputBlocks)
	{
		next->removeConnections();
	}
}

void CipherStateStartGame::onStateEnter(CipherState* cipherState)
{
	super::onStateEnter(cipherState);

	this->defer([=]()
	{
		CipherState::updateState(cipherState, CipherState::StateType::LoadInitialState);
	});
}

void CipherStateStartGame::onStateReload(CipherState* cipherState)
{
	super::onStateReload(cipherState);
}

void CipherStateStartGame::onStateExit(CipherState* cipherState)
{
	super::onStateExit(cipherState);
}
