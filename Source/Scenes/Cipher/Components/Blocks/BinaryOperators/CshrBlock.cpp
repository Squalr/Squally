#include "CshrBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/CipherConfig.h"

#include "Resources/CipherResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CshrBlock* CshrBlock::create(BlockType blockType)
{
	CshrBlock* instance = new CshrBlock(blockType);

	instance->autorelease();

	return instance;
}

CshrBlock::CshrBlock(BlockType blockType) : super(blockType, ConnectionType::Double, ConnectionType::Single, ClickableNode::create(CipherResources::Blocks_BlockTeal, CipherResources::Blocks_BlockTeal), CipherResources::Icons_CircularShiftRight, Strings::Cipher_Operations_CSHR::create())
{
}

CshrBlock::~CshrBlock()
{
}

void CshrBlock::onEnter()
{
	super::onEnter();
}

void CshrBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

unsigned char CshrBlock::compute()
{
	return this->inputLeft >> this->inputRight;
}
