#include "AddBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/ADD.h"

using namespace cocos2d;

AddBlock* AddBlock::create(bool isToolBoxItem)
{
	AddBlock* instance = new AddBlock(isToolBoxItem);

	instance->autorelease();

	return instance;
}

AddBlock::AddBlock(bool isToolBoxItem) : super(isToolBoxItem, ClickableNode::create(CipherResources::BlockDec, CipherResources::BlockDec), CipherResources::Icons_Addition, Strings::Cipher_Operations_ADD::create())
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

BlockBase* AddBlock::spawn()
{
	return AddBlock::create();
}
