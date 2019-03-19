#include "InvBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/INV.h"

using namespace cocos2d;

InvBlock* InvBlock::create(BlockType blockType)
{
	InvBlock* instance = new InvBlock(blockType);

	instance->autorelease();

	return instance;
}

InvBlock::InvBlock(BlockType blockType) : super(blockType, ConnectionType::Single, ConnectionType::Single, ClickableNode::create(CipherResources::BlockAscii, CipherResources::BlockAscii), CipherResources::Icons_Invert, Strings::Cipher_Operations_INV::create())
{
}

InvBlock::~InvBlock()
{
}

void InvBlock::onEnter()
{
	super::onEnter();
}

void InvBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

BlockBase* InvBlock::spawn()
{
	return InvBlock::create();
}
