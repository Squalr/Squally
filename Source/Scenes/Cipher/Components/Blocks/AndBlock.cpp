#include "AndBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/AND.h"

using namespace cocos2d;

AndBlock* AndBlock::create()
{
	AndBlock* instance = new AndBlock();

	instance->autorelease();

	return instance;
}

AndBlock::AndBlock() : super(ClickableNode::create(CipherResources::BlockBin, CipherResources::BlockBin), CipherResources::Icons_LogicalAnd, Strings::Cipher_Operations_AND::create())
{
}

AndBlock::~AndBlock()
{
}

void AndBlock::onEnter()
{
	super::onEnter();
}

void AndBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}
