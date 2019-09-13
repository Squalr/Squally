#include "AddBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/ADD.h"

using namespace cocos2d;

AddBlock* AddBlock::create(BlockType blockType)
{
	AddBlock* instance = new AddBlock(blockType);

	instance->autorelease();

	return instance;
}

AddBlock::AddBlock(BlockType blockType) : super(blockType, ConnectionType::Double, ConnectionType::Single, ClickableNode::create(CipherResources::Blocks_BlockDec, CipherResources::Blocks_BlockDec), CipherResources::Icons_Addition, Strings::Cipher_Operations_ADD::create())
{
}

AddBlock::~AddBlock()
{
}

void AddBlock::onEnter()
{
	super::onEnter();
}

void AddBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

unsigned char AddBlock::compute()
{
	if (this->currentInputs.size() < 2)
	{
		return (unsigned char)(0);
	}

	return this->currentInputs[0] + this->currentInputs[1];
}
