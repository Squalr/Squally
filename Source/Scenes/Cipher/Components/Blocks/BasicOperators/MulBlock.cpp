#include "MulBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/CipherConfig.h"

#include "Resources/CipherResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

MulBlock* MulBlock::create(BlockType blockType)
{
	MulBlock* instance = new MulBlock(blockType);

	instance->autorelease();

	return instance;
}

MulBlock::MulBlock(BlockType blockType) : super(blockType, ConnectionType::Double, ConnectionType::Single, ClickableNode::create(CipherResources::Blocks_BlockHex, CipherResources::Blocks_BlockHex), CipherResources::Icons_Multiplication, Strings::Cipher_Operations_MUL::create())
{
}

MulBlock::~MulBlock()
{
}

void MulBlock::onEnter()
{
	super::onEnter();
}

void MulBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

unsigned char MulBlock::compute()
{
	return this->inputLeft * this->inputRight;
}
