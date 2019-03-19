#include "GameBoard.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Input/ClickableNode.h"
#include "Events/CipherEvents.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"
#include "Scenes/Cipher/Config.h"
#include "Scenes/Cipher/Components/Blocks/BlockBase.h"
#include "Scenes/Cipher/Components/Blocks/ImmediateBlock.h"
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
	this->inputBlocks = std::vector<BlockBase*>();
	this->outputBlocks = std::vector<BlockBase*>();
	this->userBlocks = std::vector<BlockBase*>();
	this->inputContent = Node::create();
	this->outputContent = Node::create();
	this->userContent = Node::create();
	this->cipherPuzzleData = nullptr;

	for (int index = 0; index < Config::MaxInputOutputCount; index++)
	{
		this->inputBlocks.push_back(ImmediateBlock::create(false, true));
		this->outputBlocks.push_back(ImmediateBlock::create(false, true));
	}

	for (auto it = this->inputBlocks.begin(); it != this->inputBlocks.end(); it++)
	{
		this->inputContent->addChild(*it);
	}

	for (auto it = this->outputBlocks.begin(); it != this->outputBlocks.end(); it++)
	{
		this->outputContent->addChild(*it);
	}

	this->addChild(this->inputContent);
	this->addChild(this->outputContent);
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

	int index = 0;

	for (auto it = this->inputBlocks.begin(); it != this->inputBlocks.end(); it++, index++)
	{
		(*it)->setPosition(Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter + float(index - 2) * 212.0f, visibleSize.height / 2.0f + 304.0f));
	}

	index = 0;

	for (auto it = this->outputBlocks.begin(); it != this->outputBlocks.end(); it++, index++)
	{
		(*it)->setPosition(Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter + float(index - 2) * 212.0f, visibleSize.height / 2.0f - 304.0f));
	}
}

void GameBoard::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventRequestToolSpawn, [=](EventCustom* eventCustom)
	{
		CipherEvents::CipherSpawnArgs* args = static_cast<CipherEvents::CipherSpawnArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			BlockBase* newBlock = args->spawnBlockFunc();

			if (newBlock != nullptr)
			{
				this->addChild(newBlock);
				newBlock->setPosition(args->spawnCoords);
			}
		}
	}));
}

void GameBoard::loadPuzzleData(CipherPuzzleData* cipherPuzzleData)
{
	this->cipherPuzzleData = cipherPuzzleData;

	this->loadCipherAtIndex(0);
}

void GameBoard::loadCipherAtIndex(int index)
{
	std::vector<std::tuple<std::string, std::string>> inputOutputMap = this->cipherPuzzleData->getInputOutputMap();

	this->currentInput = std::get<0>(inputOutputMap[index]);
	this->currentOutput = std::get<1>(inputOutputMap[index]);
}

void GameBoard::onBeforeStateChange(CipherState* cipherState)
{
	super::onBeforeStateChange(cipherState);
}

void GameBoard::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);
}
