#include "CshlBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/CSHL.h"

using namespace cocos2d;

CshlBlock* CshlBlock::create(BlockType blockType)
{
	CshlBlock* instance = new CshlBlock(blockType);

	instance->autorelease();

	return instance;
}

CshlBlock::CshlBlock(BlockType blockType) : super(blockType, ConnectionType::Double, ConnectionType::Single, ClickableNode::create(CipherResources::Blocks_BlockTeal, CipherResources::Blocks_BlockTeal), CipherResources::Icons_CircularShiftLeft, Strings::Cipher_Operations_CSHL::create())
{
}

CshlBlock::~CshlBlock()
{
}

void CshlBlock::onEnter()
{
	super::onEnter();
}

void CshlBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

unsigned char CshlBlock::compute()
{
	if (this->currentInputs.size() < 2)
	{
		return (unsigned char)(0);
	}

	return this->currentInputs[0] << this->currentInputs[1];
}

BlockBase* CshlBlock::spawn()
{
	return CshlBlock::create();
}
