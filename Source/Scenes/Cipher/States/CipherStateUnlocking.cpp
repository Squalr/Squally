#include "CipherStateUnlocking.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Scenes/Cipher/Components/Blocks/Blocks.h"

using namespace cocos2d;

CipherStateUnlocking* CipherStateUnlocking::create()
{
	CipherStateUnlocking* instance = new CipherStateUnlocking();

	instance->autorelease();

	return instance;
}

CipherStateUnlocking::CipherStateUnlocking() : super(CipherState::StateType::Unlocking)
{
}

CipherStateUnlocking::~CipherStateUnlocking()
{
}

void CipherStateUnlocking::onBeforeStateEnter(CipherState* cipherState)
{
	super::onBeforeStateEnter(cipherState);
}

void CipherStateUnlocking::onStateEnter(CipherState* cipherState)
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

	this->performUnlockLoop(cipherState, inputBlocks, immediateBlocks,[=]()
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
}

void CipherStateUnlocking::onStateReload(CipherState* cipherState)
{
	super::onStateReload(cipherState);
}

void CipherStateUnlocking::onStateExit(CipherState* cipherState)
{
	super::onStateExit(cipherState);
}

void CipherStateUnlocking::performUnlockLoop(CipherState* cipherState, std::vector<BlockBase*> inputBlocks, std::vector<BlockBase*> immediateBlocks, std::function<void()> onExecuteComplete, int index)
{
	if (index < cipherState->inputOutputMap.size())
	{
		CipherEvents::TriggerChangeActiveCipher(CipherEvents::CipherChangeActiveCipherArgs(
			std::get<0>(cipherState->inputOutputMap[index]),
			std::get<1>(cipherState->inputOutputMap[index]),
			true
		));

		this->performExecuteLoop(inputBlocks, [=]()
		{
			this->performExecuteLoop(immediateBlocks, [=]()
			{
				bool unlockSuccessful = true;
				
				for (auto it = cipherState->outputBlocks.begin(); it != cipherState->outputBlocks.end(); it++)
				{
					unlockSuccessful &= (*it)->isMatchedValues();
				}

				CipherEvents::TriggerTryUnlockCurrentCipher(CipherEvents::UnlockArgs(index, unlockSuccessful, [=]()
				{
					if (index >= cipherState->inputOutputMap.size() - 1)
					{
						onExecuteComplete();
					}
					else
					{
						this->performUnlockLoop(cipherState, inputBlocks, immediateBlocks, onExecuteComplete, index + 1);
					}
				}));
			});
		});
	}
}

void CipherStateUnlocking::performExecuteLoop(std::vector<BlockBase*> blocks, std::function<void()> onExecuteComplete, int index)
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
