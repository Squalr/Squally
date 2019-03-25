#include "ComparisonBlockBase.h"

#include "Engine/Input/ClickableNode.h"

#include "Scenes/Cipher/Components/Blocks/Connections/OutputBolt.h"

#include "Resources/CipherResources.h"

using namespace cocos2d;

ComparisonBlockBase::ComparisonBlockBase(BlockType blockType, std::string iconResource, LocalizedString* localizedString) : super(blockType, ConnectionType::Double, ConnectionType::Double, ClickableNode::create(CipherResources::Blocks_BlockDec, CipherResources::Blocks_BlockDec), iconResource, localizedString)
{
}

ComparisonBlockBase::~ComparisonBlockBase()
{
}

unsigned char ComparisonBlockBase::compute()
{
	if (this->currentInputs.size() < 2)
	{
		return (unsigned char)(0);
	}

	return this->compare(this->currentInputs[0], this->currentInputs[1]) ? this->currentInputs[0] : this->currentInputs[1];
}

void ComparisonBlockBase::execute(std::function<void()> onExecuteComplete)
{
	this->receivedValue = this->compute();
	
	// Only perform execution when the total input count has been reached
	if (this->outputBolts.size() > 0 && this->currentInputs.size() == this->inputBolts.size())
	{
		if (this->compare(this->currentInputs[0], this->currentInputs[1]))
		{
			this->outputBolts[0]->execute(this->receivedValue, onExecuteComplete);
		}
		else
		{
			this->outputBolts[1]->execute(this->receivedValue, onExecuteComplete);
		}
	}
	else
	{
		onExecuteComplete();
	}
}
