#include "SubBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/SUB.h"

using namespace cocos2d;

SubBlock* SubBlock::create()
{
	SubBlock* instance = new SubBlock();

	instance->autorelease();

	return instance;
}

SubBlock::SubBlock() : super(ClickableNode::create(CipherResources::BlockDec, CipherResources::BlockDec), Strings::Cipher_Operations_SUB::create())
{
}

SubBlock::~SubBlock()
{
}

void SubBlock::onEnter()
{
	super::onEnter();
}

void SubBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}
