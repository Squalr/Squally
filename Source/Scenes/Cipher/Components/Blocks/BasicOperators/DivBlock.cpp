#include "DivBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/DIV.h"

using namespace cocos2d;

DivBlock* DivBlock::create(BlockType blockType)
{
	DivBlock* instance = new DivBlock(blockType);

	instance->autorelease();

	return instance;
}

DivBlock::DivBlock(BlockType blockType) : super(blockType, ConnectionType::Double, ConnectionType::Single, ClickableNode::create(CipherResources::Blocks_BlockHex, CipherResources::Blocks_BlockHex), CipherResources::Icons_Division, Strings::Cipher_Operations_DIV::create())
{
}

DivBlock::~DivBlock()
{
}

void DivBlock::onEnter()
{
	super::onEnter();
}

void DivBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

char DivBlock::compute()
{
	if (this->currentInputs.size() < 2)
	{
		return char(0);
	}

	return this->currentInputs[1] == char(0) ? char(0) : (this->currentInputs[0] / this->currentInputs[1]);
}

BlockBase* DivBlock::spawn()
{
	return DivBlock::create();
}
