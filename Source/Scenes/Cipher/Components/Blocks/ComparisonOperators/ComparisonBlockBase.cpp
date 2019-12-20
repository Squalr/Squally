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
	return this->compare(this->inputLeft, this->inputRight) ? this->inputLeft : this->inputRight;
}

void ComparisonBlockBase::execute(std::function<void()> onExecuteComplete)
{
	this->receivedValue = this->compute();
	
	// Only perform execution when the total input count has been reached
	if ((this->receivedInputs == 1 && this->inputType == BlockBase::ConnectionType::Single) || 
		(this->receivedInputs == 2 && this->inputType == BlockBase::ConnectionType::Double))
	{
		if (this->compare(this->inputLeft, this->inputRight))
		{
			this->outputBoltLeft->execute(this->receivedValue, onExecuteComplete);
		}
		else
		{
			this->outputBoltRight->execute(this->receivedValue, onExecuteComplete);
		}
	}
	else
	{
		onExecuteComplete();
	}
}
