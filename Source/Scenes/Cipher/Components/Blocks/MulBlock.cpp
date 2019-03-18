#include "MulBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/MUL.h"

using namespace cocos2d;

MulBlock* MulBlock::create()
{
	MulBlock* instance = new MulBlock();

	instance->autorelease();

	return instance;
}

MulBlock::MulBlock() : super(ClickableNode::create(CipherResources::BlockDec, CipherResources::BlockDec), Strings::Cipher_Operations_MUL::create())
{
}

MulBlock::~MulBlock()
{
}

void MulBlock::onEnter()
{
	super::onEnter();
}

void MulBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}
