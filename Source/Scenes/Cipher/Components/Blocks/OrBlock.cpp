#include "OrBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/OR.h"

using namespace cocos2d;

OrBlock* OrBlock::create(bool isToolBoxItem)
{
	OrBlock* instance = new OrBlock(isToolBoxItem);

	instance->autorelease();

	return instance;
}

OrBlock::OrBlock(bool isToolBoxItem) : super(isToolBoxItem, ClickableNode::create(CipherResources::BlockBin, CipherResources::BlockBin), CipherResources::Icons_LogicalOr, Strings::Cipher_Operations_OR::create())
{
}

OrBlock::~OrBlock()
{
}

void OrBlock::onEnter()
{
	super::onEnter();
}

void OrBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

BlockBase* OrBlock::spawn()
{
	return OrBlock::create();
}
