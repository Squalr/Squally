#include "GreaterThanBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/SHR.h"

using namespace cocos2d;

GreaterThanBlock* GreaterThanBlock::create(BlockType blockType)
{
	GreaterThanBlock* instance = new GreaterThanBlock(blockType);

	instance->autorelease();

	return instance;
}

GreaterThanBlock::GreaterThanBlock(BlockType blockType) : super(blockType, ConnectionType::Double, ConnectionType::Double, ClickableNode::create(CipherResources::Blocks_BlockDec, CipherResources::Blocks_BlockDec), CipherResources::Icons_GreaterThan, Strings::Cipher_Operations_SHR::create())
{
}

GreaterThanBlock::~GreaterThanBlock()
{
}

void GreaterThanBlock::onEnter()
{
	super::onEnter();
}

void GreaterThanBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

char GreaterThanBlock::compute()
{
	if (this->currentInputs.size() < 1)
	{
		return char(0);
	}

	return this->currentInputs[0];
}

BlockBase* GreaterThanBlock::spawn()
{
	return GreaterThanBlock::create();
}
