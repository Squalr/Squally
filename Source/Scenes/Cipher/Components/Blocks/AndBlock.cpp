#include "AndBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/AND.h"

using namespace cocos2d;

AndBlock* AndBlock::create(BlockType blockType)
{
	AndBlock* instance = new AndBlock(blockType);

	instance->autorelease();

	return instance;
}

AndBlock::AndBlock(BlockType blockType) : super(blockType, ConnectionType::Double, ConnectionType::Single, ClickableNode::create(CipherResources::Blocks_BlockBin, CipherResources::Blocks_BlockBin), CipherResources::Icons_LogicalAnd, Strings::Cipher_Operations_AND::create())
{
}

AndBlock::~AndBlock()
{
}

void AndBlock::onEnter()
{
	super::onEnter();
}

void AndBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

char AndBlock::compute()
{
	if (this->currentInputs.size() < 2)
	{
		return char(0);
	}

	return this->currentInputs[0] & this->currentInputs[1];
}

BlockBase* AndBlock::spawn()
{
	return AndBlock::create();
}
