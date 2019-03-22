#include "GameBoard.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Input/ClickableNode.h"
#include "Events/CipherEvents.h"
#include "Scenes/Cipher/CipherPuzzles/CipherPuzzleData.h"
#include "Scenes/Cipher/Config.h"
#include "Scenes/Cipher/Components/Blocks/BlockBase.h"
#include "Scenes/Cipher/Components/Blocks/Connections/Connection.h"
#include "Scenes/Cipher/Components/Blocks/DestinationBlock.h"
#include "Scenes/Cipher/Components/Blocks/ImmediateBlock.h"
#include "Scenes/Cipher/Components/Blocks/SourceBlock.h"
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
	this->inputBlocks = std::vector<SourceBlock*>();
	this->outputBlocks = std::vector<DestinationBlock*>();
	this->userBlocks = std::vector<BlockBase*>();
	this->userConnections = std::vector<Connection*>();
	this->inputContent = Node::create();
	this->outputContent = Node::create();
	this->blockContent = Node::create();
	this->connectionContent = Node::create();
	this->gameAreaDebug = LayerColor::create(Color4B(32, 128, 32, 128), Config::GameAreaWidth, Config::GameAreaHeight);

	for (int index = 0; index < Config::MaxInputOutputCount; index++)
	{
		this->inputBlocks.push_back(SourceBlock::create(index));
		this->outputBlocks.push_back(DestinationBlock::create(index));
	}

	for (auto it = this->inputBlocks.begin(); it != this->inputBlocks.end(); it++)
	{
		this->inputContent->addChild(*it);
	}

	for (auto it = this->outputBlocks.begin(); it != this->outputBlocks.end(); it++)
	{
		this->outputContent->addChild(*it);
	}

	this->addChild(this->gameAreaDebug);
	this->addChild(this->outputContent);
	this->addChild(this->inputContent);
	this->addChild(this->blockContent);
	this->addChild(this->connectionContent);
}

GameBoard::~GameBoard()
{
}

void GameBoard::onEnter()
{
	super::onEnter();

	this->blockContent->removeAllChildren();
	this->connectionContent->removeAllChildren();
}

void GameBoard::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->gameAreaDebug->setPosition(Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter - Config::GameAreaWidth / 2.0f, visibleSize.height / 2.0f - Config::GameAreaHeight / 2.0f));

	int index = 0;

	for (auto it = this->inputBlocks.begin(); it != this->inputBlocks.end(); it++, index++)
	{
		(*it)->setPosition(Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter + float(index - Config::MaxInputOutputCount / 2) * Config::IOSpacing, visibleSize.height / 2.0f + Config::IOVerticalOffset));
	}

	index = 0;

	for (auto it = this->outputBlocks.begin(); it != this->outputBlocks.end(); it++, index++)
	{
		(*it)->setPosition(Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter + float(index - Config::MaxInputOutputCount / 2) * Config::IOSpacing, visibleSize.height / 2.0f - Config::IOVerticalOffset));
	}
}

void GameBoard::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventRequestBlockSpawn, [=](EventCustom* eventCustom)
	{
		CipherEvents::CipherBlockSpawnArgs* args = static_cast<CipherEvents::CipherBlockSpawnArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			BlockBase* newBlock = args->spawnBlockFunc();

			if (newBlock != nullptr)
			{
				this->blockContent->addChild(newBlock);
				newBlock->setPosition(args->spawnCoords);
			}
		}
	}));
}

void GameBoard::onDeveloperModeEnable()
{
	super::onDeveloperModeEnable();

	this->gameAreaDebug->setVisible(true);
}

void GameBoard::onDeveloperModeDisable()
{
	super::onDeveloperModeEnable();

	this->gameAreaDebug->setVisible(false);
}

void GameBoard::onBeforeStateChange(CipherState* cipherState)
{
	super::onBeforeStateChange(cipherState);
}

void GameBoard::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);

	this->currentCipherState = cipherState;

	switch(cipherState->stateType)
	{
		case CipherState::StateType::LoadInitialState:
		{
			this->loadCipherAtIndex(0);
			break;
		}
		default:
		{
			break;
		}
	}
}

void GameBoard::loadCipherAtIndex(int index)
{
	this->currentInput = std::get<0>(this->currentCipherState->inputOutputMap[index]);
	this->currentOutput = std::get<1>(this->currentCipherState->inputOutputMap[index]);
}
