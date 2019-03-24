#include "ShlBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/SHL.h"

using namespace cocos2d;

ShlBlock* ShlBlock::create(BlockType blockType)
{
	ShlBlock* instance = new ShlBlock(blockType);

	instance->autorelease();

	return instance;
}

ShlBlock::ShlBlock(BlockType blockType) : super(blockType, ConnectionType::Double, ConnectionType::Single, ClickableNode::create(CipherResources::Blocks_BlockTeal, CipherResources::Blocks_BlockTeal), CipherResources::Icons_ShiftLeft, Strings::Cipher_Operations_SHL::create())
{
}

ShlBlock::~ShlBlock()
{
}

void ShlBlock::onEnter()
{
	super::onEnter();
}

void ShlBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

char ShlBlock::compute()
{
	if (this->currentInputs.size() < 2)
	{
		return char(0);
	}

	return this->currentInputs[1] == char(0) ? char(0) : (this->currentInputs[0] | this->currentInputs[1]);
}

BlockBase* ShlBlock::spawn()
{
	return ShlBlock::create();
}
