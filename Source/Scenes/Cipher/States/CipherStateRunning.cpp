#include "CipherStateRunning.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Scenes/Cipher/Components/Blocks/Blocks.h"

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

	std::vector<BlockBase*> inputBlocks = std::vector<BlockBase*>();
	std::vector<BlockBase*> immediateBlocks = std::vector<BlockBase*>();

	for (auto it = cipherState->inputBlocks.begin(); it != cipherState->inputBlocks.end(); it++)
	{
		inputBlocks.push_back(*it);
	}

	for (auto it = cipherState->userBlocks.begin(); it != cipherState->userBlocks.end(); it++)
	{
		if (dynamic_cast<ImmediateBlock*>(*it) != nullptr)
		{
			immediateBlocks.push_back(*it);
		}
	}

	this->performExecuteLoop(inputBlocks, [=]()
	{
		this->performExecuteLoop(immediateBlocks, [=]()
		{
			// TODO: Check for victory and whatnot
			this->runAction(Sequence::create(
				DelayTime::create(0.1f),
				CallFunc::create([=]()
				{
					CipherState::updateState(cipherState, CipherState::StateType::Neutral);
				}),
				nullptr
			));
		});
	});
}

void CipherStateRunning::onStateReload(CipherState* cipherState)
{
	super::onStateReload(cipherState);
}

void CipherStateRunning::onStateExit(CipherState* cipherState)
{
	super::onStateExit(cipherState);
}

void CipherStateRunning::performExecuteLoop(std::vector<BlockBase*> blocks, std::function<void()> onExecuteComplete, int index)
{
	if (index < blocks.size())
	{
		// Execute the input block at the current index
		blocks[index]->execute([=]
		{
			// Afterwards, execute the next input
			this->performExecuteLoop(blocks, onExecuteComplete, index + 1);
		});
	}
	else
	{
		onExecuteComplete();
	}
}
