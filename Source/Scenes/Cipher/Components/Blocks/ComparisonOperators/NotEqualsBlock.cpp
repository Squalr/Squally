#include "NotEqualsBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/SHR.h"

using namespace cocos2d;

NotEqualsBlock* NotEqualsBlock::create(BlockType blockType)
{
	NotEqualsBlock* instance = new NotEqualsBlock(blockType);

	instance->autorelease();

	return instance;
}

NotEqualsBlock::NotEqualsBlock(BlockType blockType) : super(blockType, ConnectionType::Double, ConnectionType::Double, ClickableNode::create(CipherResources::Blocks_BlockDec, CipherResources::Blocks_BlockDec), CipherResources::Icons_NotEquals, Strings::Cipher_Operations_SHR::create())
{
}

NotEqualsBlock::~NotEqualsBlock()
{
}

void NotEqualsBlock::onEnter()
{
	super::onEnter();
}

void NotEqualsBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

char NotEqualsBlock::compute()
{
	if (this->currentInputs.size() < 1)
	{
		return char(0);
	}

	return this->currentInputs[0];
}

BlockBase* NotEqualsBlock::spawn()
{
	return NotEqualsBlock::create();
}
