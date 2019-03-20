#include "SourceBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"
#include "Resources/UIResources.h"

#include "Strings/Cipher/Operations/Immediate.h"

using namespace cocos2d;

SourceBlock* SourceBlock::create()
{
	SourceBlock* instance = new SourceBlock();

	instance->autorelease();

	return instance;
}

SourceBlock::SourceBlock() : super(BlockType::Static, ConnectionType::None, ConnectionType::Single, ClickableNode::create(CipherResources::Blocks_BlockDecLong, CipherResources::Blocks_BlockDecLong), UIResources::EmptyImage, Strings::Cipher_Operations_Immediate::create())
{
}

SourceBlock::~SourceBlock()
{
}

void SourceBlock::onEnter()
{
	super::onEnter();
}

void SourceBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

BlockBase* SourceBlock::spawn()
{
	return SourceBlock::create();
}
