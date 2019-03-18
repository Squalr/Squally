#include "InvBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/INV.h"

using namespace cocos2d;

InvBlock* InvBlock::create()
{
	InvBlock* instance = new InvBlock();

	instance->autorelease();

	return instance;
}

InvBlock::InvBlock() : super(ClickableNode::create(CipherResources::BlockDec, CipherResources::BlockDec), Strings::Cipher_Operations_INV::create())
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
