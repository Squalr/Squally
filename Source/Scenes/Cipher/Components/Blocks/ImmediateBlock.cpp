#include "ImmediateBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/Immediate.h"

using namespace cocos2d;

ImmediateBlock* ImmediateBlock::create(BlockType blockType)
{
	ImmediateBlock* instance = new ImmediateBlock(blockType);

	instance->autorelease();

	return instance;
}

ImmediateBlock::ImmediateBlock(BlockType blockType) : super(blockType, ConnectionType::None, ConnectionType::Single, ClickableNode::create(CipherResources::BlockAscii, CipherResources::BlockAscii), CipherResources::Icons_Immediate, Strings::Cipher_Operations_Immediate::create())
{
}

ImmediateBlock::~ImmediateBlock()
{
}

void ImmediateBlock::onEnter()
{
	super::onEnter();
}

void ImmediateBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

BlockBase* ImmediateBlock::spawn()
{
	return ImmediateBlock::create(BlockType::Normal);
}
