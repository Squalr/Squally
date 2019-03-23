#include "BruteForceBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/BruteForce.h"

using namespace cocos2d;

BruteForceBlock* BruteForceBlock::create(BlockType blockType)
{
	BruteForceBlock* instance = new BruteForceBlock(blockType);

	instance->autorelease();

	return instance;
}

BruteForceBlock::BruteForceBlock(BlockType blockType) : super(blockType, ConnectionType::None, ConnectionType::Single, ClickableNode::create(CipherResources::Blocks_BlockAscii, CipherResources::Blocks_BlockAscii), CipherResources::Icons_BruteForce, Strings::Cipher_Operations_BruteForce::create())
{
}

BruteForceBlock::~BruteForceBlock()
{
}

void BruteForceBlock::onEnter()
{
	super::onEnter();
}

void BruteForceBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

char BruteForceBlock::compute()
{
	return char(0);
}

BlockBase* BruteForceBlock::spawn()
{
	return BruteForceBlock::create();
}
