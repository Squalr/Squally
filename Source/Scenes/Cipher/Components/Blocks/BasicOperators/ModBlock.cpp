#include "ModBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/MOD.h"

using namespace cocos2d;

ModBlock* ModBlock::create(BlockType blockType)
{
	ModBlock* instance = new ModBlock(blockType);

	instance->autorelease();

	return instance;
}

ModBlock::ModBlock(BlockType blockType) : super(blockType, ConnectionType::Double, ConnectionType::Single, ClickableNode::create(CipherResources::Blocks_BlockGreen, CipherResources::Blocks_BlockGreen), CipherResources::Icons_Modulo, Strings::Cipher_Operations_MOD::create())
{
}

ModBlock::~ModBlock()
{
}

void ModBlock::onEnter()
{
	super::onEnter();
}

void ModBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

unsigned char ModBlock::compute()
{
	if (this->currentInputs.size() < 2)
	{
		return (unsigned char)(0);
	}

	return this->currentInputs[1] == (unsigned char)(0) ? (unsigned char)(0) : (this->currentInputs[0] % this->currentInputs[1]);
}
