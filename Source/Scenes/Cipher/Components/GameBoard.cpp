#include "GameBoard.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"
#include "Scenes/Cipher/Components/Blocks/BlockBase.h"
#include "Scenes/Cipher/CipherState.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

GameBoard* GameBoard::create()
{
	GameBoard* instance = new GameBoard();

	instance->autorelease();

	return instance;
}

GameBoard::GameBoard()
{
	this->inputOutputBlocks = std::vector<BlockBase*>();
}

GameBoard::~GameBoard()
{
}

void GameBoard::onEnter()
{
	super::onEnter();
}

void GameBoard::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void GameBoard::loadPuzzleData(CipherPuzzleData* cipherPuzzleData)
{
}

void GameBoard::onBeforeStateChange(CipherState* cipherState)
{
	super::onBeforeStateChange(cipherState);
}

void GameBoard::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);
}
