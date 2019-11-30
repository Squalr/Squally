#include "SubBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

SubBlock* SubBlock::create(BlockType blockType)
{
	SubBlock* instance = new SubBlock(blockType);

	instance->autorelease();

	return instance;
}

SubBlock::SubBlock(BlockType blockType) : super(blockType, ConnectionType::Double, ConnectionType::Single, ClickableNode::create(CipherResources::Blocks_BlockDec, CipherResources::Blocks_BlockDec), CipherResources::Icons_Subtraction, Strings::Cipher_Operations_SUB::create())
{
}

SubBlock::~SubBlock()
{
}

void SubBlock::onEnter()
{
	super::onEnter();
}

void SubBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

unsigned char SubBlock::compute()
{
	if (this->currentInputs.size() < 2)
	{
		return (unsigned char)(0);
	}

	return this->currentInputs[0] - this->currentInputs[1];
}
