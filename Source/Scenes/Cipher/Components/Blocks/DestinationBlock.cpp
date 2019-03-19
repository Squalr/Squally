#include "DestinationBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/Immediate.h"

using namespace cocos2d;

DestinationBlock* DestinationBlock::create()
{
	DestinationBlock* instance = new DestinationBlock();

	instance->autorelease();

	return instance;
}

DestinationBlock::DestinationBlock() : super(BlockType::Static, ConnectionType::Single, ConnectionType::None, ClickableNode::create(CipherResources::BlockDecLong, CipherResources::BlockDecLong), CipherResources::Icons_Immediate, Strings::Cipher_Operations_Immediate::create())
{
}

DestinationBlock::~DestinationBlock()
{
}

void DestinationBlock::onEnter()
{
	super::onEnter();
}

void DestinationBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

BlockBase* DestinationBlock::spawn()
{
	return DestinationBlock::create();
}
