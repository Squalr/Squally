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

	for (auto next : cipherState->inputBlocks)
	{
		inputBlocks.push_back(next);
	}

	for (auto next : cipherState->userBlocks)
	{
		if (dynamic_cast<ImmediateBlock*>(next) != nullptr)
		{
			immediateBlocks.push_back(next);
		}
	}

	this->performUnlockLoop(cipherState, inputBlocks, immediateBlocks, [=](bool success)
	{
		if (success)
		{
			CipherState::updateState(cipherState, CipherState::StateType::Victory);
		}
		else
		{
			CipherState::updateState(cipherState, CipherState::StateType::Neutral);
		}
		
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

void CipherStateUnlocking::performUnlockLoop(CipherState* cipherState, std::vector<BlockBase*> inputBlocks, std::vector<BlockBase*> immediateBlocks, std::function<void(bool success)> onExecuteComplete, int index)
{
	static bool unlockSuccessful = true;

	// Reset state
	if (index == 0)
	{
		unlockSuccessful = true;
	}

	if (cipherState->inputOutputMap.empty())
	{
		onExecuteComplete(true);
		return;
	}

	if (index < int(cipherState->inputOutputMap.size()))
	{
		CipherEvents::TriggerChangeActiveCipher(CipherEvents::CipherChangeActiveCipherArgs(
			std::get<0>(cipherState->inputOutputMap[index]),
			std::get<1>(cipherState->inputOutputMap[index]),
			index,
			true
		));

		this->performExecuteLoop(cipherState, inputBlocks, [=]()
		{
			this->performExecuteLoop(cipherState, immediateBlocks, [=]()
			{
				bool currentUnlockSuccessful = true;
				
				for (auto next : cipherState->outputBlocks)
				{
					currentUnlockSuccessful &= next->isMatchedValues();
				}

				CipherEvents::TriggerTryUnlockCurrentCipher(CipherEvents::UnlockArgs(index, currentUnlockSuccessful, [=]()
				{
					// Re-enter the unlocking state
					CipherState::updateState(cipherState, CipherState::StateType::Unlocking);

					unlockSuccessful &= currentUnlockSuccessful;

					if (index >= int(cipherState->inputOutputMap.size()) - 1)
					{
						onExecuteComplete(unlockSuccessful);
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

void CipherStateUnlocking::performExecuteLoop(CipherState* cipherState, std::vector<BlockBase*> blocks, std::function<void()> onExecuteComplete, int index)
{
	if (index < int(blocks.size()))
	{
		// Execute the input block at the current index
		blocks[index]->execute([=]
		{
			// Afterwards, execute the next input
			this->performExecuteLoop(cipherState, blocks, onExecuteComplete, index + 1);
		});
	}
	else
	{
		onExecuteComplete();
	}
}
