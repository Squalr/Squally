#include "CipherState.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Utils/StrUtils.h"
#include "Scenes/Cipher/CipherPuzzleData.h"
#include "Scenes/Cipher/Config.h"
#include "Scenes/Cipher/Components/Blocks/BlockBase.h"
#include "Scenes/Cipher/Components/Blocks/Blocks.h"
#include "Scenes/Cipher/Components/Blocks/Connections/Connection.h"
#include "Scenes/Cipher/CipherState.h"

#include "Resources/CipherResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

CipherState* CipherState::create()
{
	CipherState* instance = new CipherState();

	instance->autorelease();

	return instance;
}

CipherState::CipherState()
	: stateType(StateType::EmptyState),
	updateStateCallback(nullptr),
	cipherLockPointer(nullptr)
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
	this->puzzleData = nullptr;
	this->displayDataType = CipherEvents::DisplayDataType::Ascii;

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

CipherState::~CipherState()
{
}

void CipherState::initializePositions()
{
	SmartNode::initializePositions();

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
		(*it)->setPosition(Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter + float(index - Config::MaxInputOutputCount / 2) * Config::IOSpacing, visibleSize.height / 2.0f - Config::IOVerticalOffset + 16.0f));
	}
}

void CipherState::initializeListeners()
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
				this->userBlocks.push_back(newBlock);
				this->blockContent->addChild(newBlock);
				newBlock->setPosition(args->spawnCoords);
			}
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventChangeDisplayDataType, [&](EventCustom* eventCustom)
	{
		CipherEvents::CipherChangeDisplayDataTypeArgs* args = static_cast<CipherEvents::CipherChangeDisplayDataTypeArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->displayDataType = args->displayDataType;
		}
	}));
}

void CipherState::onDeveloperModeEnable()
{
	super::onDeveloperModeEnable();

	this->gameAreaDebug->setVisible(true);
}

void CipherState::onDeveloperModeDisable()
{
	super::onDeveloperModeEnable();

	this->gameAreaDebug->setVisible(false);
}

void CipherState::updateState(CipherState* cipherState, StateType newState)
{
	cipherState->previousStateType = cipherState->stateType;
	cipherState->stateType = newState;
	cipherState->clearInteraction();

	switch (newState)
	{
		case StateType::GameStart:
		{
			cipherState->gameStartTime = std::chrono::high_resolution_clock::now();

			CipherEvents::TriggerChangeDisplayDataType(CipherEvents::CipherChangeDisplayDataTypeArgs(cipherState->displayDataType));
			break;
		}
		case StateType::GameEnd:
		{
			cipherState->gameEndTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = cipherState->gameEndTime - cipherState->gameStartTime;
			cipherState->gameDurationInSeconds = (int)(elapsed.count());
			break;
		}
		default:
		{
			break;
		}
	}

	CipherEvents::TriggerRequestStateUpdate(cipherState);
	CipherEvents::TriggerBeforeStateUpdate(cipherState);
	CipherEvents::TriggerOnStateUpdate(cipherState);
}

void CipherState::clearInteraction()
{
}

void CipherState::loadPuzzleData(CipherPuzzleData* puzzleData)
{
	if (this->puzzleData != nullptr)
	{
		this->removeChild(this->puzzleData);
	}

	if (puzzleData != nullptr)
	{
		this->puzzleData = puzzleData->clone();
		this->addChild(this->puzzleData);
	}
}

void CipherState::loadCipherAtIndex(int index)
{
	if (index >= 0 && index < this->inputOutputMap.size())
	{
		this->currentInput = std::get<0>(this->inputOutputMap[index]);
		this->currentOutput = std::get<1>(this->inputOutputMap[index]);
	}
}

bool CipherState::isHardModeEnabled()
{
	return false;
}
