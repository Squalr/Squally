#include "CipherStateLoadInitialState.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCDirector.h"

#include "Scenes/Cipher/CipherPuzzleData.h"
#include "Scenes/Cipher/Components/Blocks/Blocks.h"
#include "Scenes/Cipher/Config.h"

using namespace cocos2d;

CipherStateLoadInitialState* CipherStateLoadInitialState::create()
{
	CipherStateLoadInitialState* instance = new CipherStateLoadInitialState();

	instance->autorelease();

	return instance;
}

CipherStateLoadInitialState::CipherStateLoadInitialState() : super(CipherState::StateType::LoadInitialState)
{
	this->spawnMap = std::map<std::string, std::function<void(int, int)>>();
	
	this->buildSpawnMap();
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
		if (cipherState->isHardModeEnabled())
		{
			cipherState->inputOutputMap = cipherState->puzzleData->getInputOutputMapHard();
			cipherState->tokens = cipherState->puzzleData->getHardTokens();
		}
		else
		{
			cipherState->inputOutputMap = cipherState->puzzleData->getInputOutputMapEasy();
			cipherState->tokens = cipherState->puzzleData->getEasyTokens();
		}
	}
	else
	{
		cipherState->inputOutputMap = { };
		cipherState->tokens = { };
	}
	
	
	cipherState->loadCipherAtIndex(0);
	this->spawnBlocks(cipherState);
}

void CipherStateLoadInitialState::onStateEnter(CipherState* cipherState)
{
	super::onStateEnter(cipherState);
	
	this->defer([=]()
	{
		CipherState::updateState(cipherState, CipherState::StateType::Neutral);
	});
}

void CipherStateLoadInitialState::onStateReload(CipherState* cipherState)
{
	super::onStateReload(cipherState);
}

void CipherStateLoadInitialState::onStateExit(CipherState* cipherState)
{
	super::onStateExit(cipherState);
}

void CipherStateLoadInitialState::buildSpawnMap()
{
	for (int index = 0; index < 256; index++)
	{
		std::string token = std::to_string(index);

		this->spawnMap[token] = [=](int index, int total)
		{
			this->spawnBlock(ImmediateBlock::create((unsigned char)(index)), index, total);
		};
	}

	// Basic operators
	this->spawnMap["+"] = [=](int index, int total)
	{
		this->spawnBlock(AddBlock::create(), index, total);
	};
	this->spawnMap["/"] = [=](int index, int total)
	{
		this->spawnBlock(DivBlock::create(), index, total);
	};
	this->spawnMap["%"] = [=](int index, int total)
	{
		this->spawnBlock(ModBlock::create(), index, total);
	};
	this->spawnMap["*"] = [=](int index, int total)
	{
		this->spawnBlock(MulBlock::create(), index, total);
	};
	this->spawnMap["-"] = [=](int index, int total)
	{
		this->spawnBlock(SubBlock::create(), index, total);
	};

	// Binary operators
	this->spawnMap["&"] = [=](int index, int total)
	{
		this->spawnBlock(AndBlock::create(), index, total);
	};
	this->spawnMap["&&"] = [=](int index, int total)
	{
		this->spawnBlock(AndBlock::create(), index, total);
	};
	this->spawnMap["<<<"] = [=](int index, int total)
	{
		this->spawnBlock(CshlBlock::create(), index, total);
	};
	this->spawnMap[">>>"] = [=](int index, int total)
	{
		this->spawnBlock(CshrBlock::create(), index, total);
	};
	this->spawnMap["~"] = [=](int index, int total)
	{
		this->spawnBlock(InvBlock::create(), index, total);
	};
	this->spawnMap["|"] = [=](int index, int total)
	{
		this->spawnBlock(OrBlock::create(), index, total);
	};
	this->spawnMap["||"] = [=](int index, int total)
	{
		this->spawnBlock(OrBlock::create(), index, total);
	};
	this->spawnMap["<<"] = [=](int index, int total)
	{
		this->spawnBlock(ShlBlock::create(), index, total);
	};
	this->spawnMap[">>"] = [=](int index, int total)
	{
		this->spawnBlock(ShrBlock::create(), index, total);
	};
	this->spawnMap["^"] = [=](int index, int total)
	{
		this->spawnBlock(XorBlock::create(), index, total);
	};

	// Comparison operators
	this->spawnMap["="] = [=](int index, int total)
	{
		this->spawnBlock(EqualsBlock::create(), index, total);
	};
	this->spawnMap["=="] = [=](int index, int total)
	{
		this->spawnBlock(EqualsBlock::create(), index, total);
	};
	this->spawnMap[">"] = [=](int index, int total)
	{
		this->spawnBlock(GreaterThanBlock::create(), index, total);
	};
	this->spawnMap[">="] = [=](int index, int total)
	{
		this->spawnBlock(GreaterThanOrEqualsBlock::create(), index, total);
	};
	this->spawnMap["<"] = [=](int index, int total)
	{
		this->spawnBlock(LessThanBlock::create(), index, total);
	};
	this->spawnMap["<="] = [=](int index, int total)
	{
		this->spawnBlock(LessThanOrEqualsBlock::create(), index, total);
	};
	this->spawnMap["!="] = [=](int index, int total)
	{
		this->spawnBlock(NotEqualsBlock::create(), index, total);
	};

	// Special operators
	this->spawnMap["b"] = [=](int index, int total)
	{
		this->spawnBlock(BruteForceBlock::create(), index, total);
	};
	this->spawnMap["B"] = [=](int index, int total)
	{
		this->spawnBlock(BruteForceBlock::create(), index, total);
	};
	this->spawnMap["s"] = [=](int index, int total)
	{
		this->spawnBlock(SplitterBlock::create(), index, total);
	};
	this->spawnMap["S"] = [=](int index, int total)
	{
		this->spawnBlock(SplitterBlock::create(), index, total);
	};
}

void CipherStateLoadInitialState::spawnBlocks(CipherState* cipherState)
{
	if (cipherState == nullptr)
	{
		return;
	}

	int total = cipherState->tokens.size();
	
	for (int index = 0; index < total; index++)
	{
		std::string token = cipherState->tokens[index];

		if (this->spawnMap.find(token) != this->spawnMap.end())
		{
			this->spawnMap[token](index, total);
		}
	}
}

void CipherStateLoadInitialState::spawnBlock(BlockBase* block, int index, int total)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 center = Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter, visibleSize.height / 2.0f);

	float possibleOffsetX = Config::GameAreaWidth / 2.0f - 128.0f;
	float possibleOffsetY = Config::GameAreaHeight / 2.0f - 256.0f;

	Vec2 position = center + Vec2(RandomHelper::random_real(-possibleOffsetX, possibleOffsetX), RandomHelper::random_real(-possibleOffsetY, possibleOffsetY));

	block->setSpawnPosition(position);

	CipherEvents::TriggerRequestBlockSpawn(CipherEvents::CipherBlockSpawnArgs(block, position));
}
